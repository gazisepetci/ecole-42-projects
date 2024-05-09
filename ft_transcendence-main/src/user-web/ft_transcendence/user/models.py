from django.db import models
from django.db.models import UniqueConstraint, CheckConstraint, Q, F
from django.contrib.auth.models import AbstractBaseUser, BaseUserManager, PermissionsMixin
from django.utils.translation import gettext_lazy as _
from django.conf import settings

from django_otp.plugins.otp_email.models import EmailDevice
from django_otp.plugins.otp_totp.models import TOTPDevice

import os

class UserManager(BaseUserManager):

    def create_user(self, username, email, password=None, **extra_fields):

        if not username:
            raise ValueError(_('You must provide a username'))
        if not email:
            raise ValueError(_('You must provide an email address'))

        username = AbstractBaseUser.normalize_username(username)
        email = self.normalize_email(email)
        user = self.model(username=username, email=email, **extra_fields)
        # If password is None, then runs self.set_unusable_password
        user.set_password(password)
        user.save()

        return user

    def create_superuser(self, username, email, password, **extra_fields):

        extra_fields.setdefault('is_staff', True)
        extra_fields.setdefault('is_superuser', True)

        if extra_fields.get('is_staff') != True:
            raise ValueError(_('Superuser must be assigned to is_staff=True'))
        if extra_fields.get('is_superuser') != True:
            raise ValueError(_('Superuser must be assigned to is_superuser=True'))

        return self.create_user(username, email, password, **extra_fields)

class User(AbstractBaseUser, PermissionsMixin):

    class TwoFAType(models.IntegerChoices):
        NONE = 1, _("None")
        EMAIL = 2, _("Email")
        TOTP = 3, _("TOTP")

    def user_directory_path(self, filename):
        return "image/user/{0}{1}".format(self.pk,
                                          os.path.splitext(filename)[1])

    username = models.CharField(_('username'), max_length=25, unique=True)
    email = models.EmailField(_('email address'), unique=True)
    image = models.ImageField(_('user image'), upload_to=user_directory_path, blank=True,
                              default="image/default/user.png")
    is_42authenticated = models.BooleanField(_('is user authenticated by 42'), default=False)
    two_fa_auth_type = models.IntegerField(choices=TwoFAType, default=TwoFAType.NONE)
    #profile_image = models.URLField(_('profile image URL'), null=True, blank=True)

    is_staff = models.BooleanField(default=False)
    is_active = models.BooleanField(default=True)

    USERNAME_FIELD = "username"
    REQUIRED_FIELDS = ["email"]

    objects = UserManager()

    def __str__(self):
        return self.username

    def register_otp_device(self, type : TwoFAType):

        if self.two_fa_auth_type != self.TwoFAType.NONE: # Lazy test
            raise Exception("User already has a registered device")

        if type == self.TwoFAType.EMAIL:
            device = EmailDevice.objects.create(user=self, name="Email")
            self.two_fa_auth_type = self.TwoFAType.EMAIL
            self.save()
            return device
        elif type == self.TwoFAType.TOTP:
            device = TOTPDevice.objects.create(user=self, name="Auth App")
            self.two_fa_auth_type = self.TwoFAType.TOTP
            self.save()
            return device
        else:
            raise Exception("Adding other devices is not implemented")

        return None

    def remove_otp_device(self):
        if self.two_fa_auth_type == self.TwoFAType.EMAIL:
            EmailDevice.objects.devices_for_user(user=self).delete()
        elif self.two_fa_auth_type == self.TwoFAType.TOTP:
            TOTPDevice.objects.devices_for_user(user=self).delete()
        else:
            raise Exception("Removing other devices is not implemented")

        self.two_fa_auth_type = self.TwoFAType.NONE
        self.save()


class UserRelationshipManager(models.Manager):

    def get_type(self, sender: User, receiver: User):
        user1, user2 = sorted((sender.pk, receiver.pk))

        try:
            record = UserRelationship.objects.get(user1_id=user1, user2_id=user2)

            if record.is_friends():
                return "friend"
            elif record.is_blocking_mutual() or record.is_blocking_other(sender.pk):
                return "blocking"
            elif record.is_pending_other(sender.pk):
                return "sent"
            elif record.is_pending_other(receiver.pk):
                return "receiving"
            else:
                return "blocked"
            
        except UserRelationship.DoesNotExist:
            return "none"

    def incoming_requests_set(self, receiver: User) -> set[User]:
        """Returns a set of users who sent friend requests to receiver"""
        recv_as_user1 = UserRelationship.objects.filter(user1=receiver, type=UserRelationship.RelationshipType.PENDING21)
        recv_as_user2 = UserRelationship.objects.filter(user2=receiver, type=UserRelationship.RelationshipType.PENDING12)

        sending = set()

        for relation in recv_as_user1:
            sending.add(relation.user2)
        for relation in recv_as_user2:
            sending.add(relation.user1)

        return sending

    def friends_set(self, user: User) -> set[User]:
        relations = UserRelationship.objects.filter(Q(user1=user) | Q(user2=user), type=UserRelationship.RelationshipType.FRIENDS)

        friends = set()

        for relation in relations:
            if relation.user1.username == user.username:
                friends.add(relation.user2)
            else:
                friends.add(relation.user1)

        return friends
            

    def add_friend(self, sender: User, receiver: User):
        user1, user2 = sorted((sender.pk, receiver.pk))

        if sender.pk == user1:
            type = UserRelationship.RelationshipType.PENDING12
        else:
            type = UserRelationship.RelationshipType.PENDING21

        try:
            record = UserRelationship.objects.get(user1_id=user1, user2_id=user2)
            if record.is_pending_other(receiver.pk):
                record.type = UserRelationship.RelationshipType.FRIENDS
                record.save()
                return True
            return False
        except UserRelationship.DoesNotExist:
            UserRelationship.objects.create(user1_id=user1, user2_id=user2,
                                            type=type)
            return True

    def remove_friend(self, sender, receiver):
        user1, user2 = sorted((sender.pk, receiver.pk))

        try:
            record = UserRelationship.objects.get(user1_id=user1, user2_id=user2)
            if record.is_pending_other(receiver.pk) or\
                record.is_pending_other(sender.pk) or record.is_friends():
                record.delete()
                return True
            return False
        except UserRelationship.DoesNotExist:
            return False

    def block_user(self, sender, receiver):
        user1, user2 = sorted((sender.pk, receiver.pk))

        if sender.pk == user1:
            type = UserRelationship.RelationshipType.BLOCK12
        else:
            type = UserRelationship.RelationshipType.BLOCK21

        try:
            record = UserRelationship.objects.get(user1_id=user1, user2_id=user2)
            if record.is_blocking_other(receiver.pk):
                record.type = UserRelationship.RelationshipType.BLOCKS
            else:
                record.type = type
            record.save()
            return True
        except UserRelationship.DoesNotExist:
            UserRelationship.objects.create(user1_id=user1, user2_id=user2,
                                            type=type)
            return True


    def unblock_user(self, sender, receiver):
        user1, user2 = sorted((sender.pk, receiver.pk))

        try:
            record = UserRelationship.objects.get(user1_id=user1, user2_id=user2)
            if record.is_blocking_mutual():
                if receiver.pk == user1:
                    type = UserRelationship.RelationshipType.BLOCK12
                else:
                    type = UserRelationship.RelationshipType.BLOCK21
                record.type = type
                record.save()
                return True
            elif record.is_blocking_other(sender.pk):
                record.delete()
                return True
            return False
        except UserRelationship.DoesNotExist:
            return False

class UserRelationship(models.Model):
    class Meta:
        constraints = [
            UniqueConstraint(fields=["user1", "user2"], name="relationship_index_constraint"),
            CheckConstraint(check=Q(user2__gt=F('user1')), name="user2__gt_user1"),
        ]

    class RelationshipType(models.TextChoices):
        PENDING12 = "P12", _("User1 sent friend request to User2")
        PENDING21 = "P21", _("User2 sent friend request to User1")
        FRIENDS = "FRN", _("User1 and User2 are friends")
        BLOCK12 = "B12", _("User1 blocked User2")
        BLOCK21 = "B21", _("User2 blocked User1")
        BLOCKS = "BLK", _("User1 and User2 blocked each other")

        __empty__ = _("Unknown")

    objects = UserRelationshipManager()

    user1 = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.CASCADE,
                              related_name="userRelationship_user1")
    user2 = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.CASCADE,
                              related_name="userRelationship_user2")
    type = models.CharField(max_length=3, choices=RelationshipType,
                            default=RelationshipType.PENDING12)

    def __str__(self):
        return str(self.user1) + " & " + str(self.user2)

    def is_pending_other(self, from_pk):
        if from_pk == self.user1.pk:
            return self.is_pending_user1()
        return self.is_pending_user2()

    def is_friends(self):
        return self.type == self.RelationshipType.FRIENDS

    def is_blocking_other(self, from_pk):
        if from_pk == self.user1.pk:
            return self.is_blocking_user1()
        return self.is_blocking_user2()

    def is_blocking_mutual(self):
        return self.type == self.RelationshipType.BLOCKS

    def is_pending_user1(self):
        return self.type == self.RelationshipType.PENDING12
    def is_pending_user2(self):
        return self.type == self.RelationshipType.PENDING21
    def is_blocking_user1(self):
        return self.type == self.RelationshipType.BLOCK12
    def is_blocking_user2(self):
        return self.type == self.RelationshipType.BLOCK21
