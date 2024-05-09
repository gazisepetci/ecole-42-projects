from django.contrib.auth import get_user_model
from rest_framework import serializers
from django.utils.translation import gettext_lazy as _

class UserLoginSerializer(serializers.Serializer):
    username = serializers.CharField(label=_("Username"), max_length=20)
    password = serializers.CharField(label=_("Password"), max_length=20)

    class Meta:
        model = get_user_model()
        fields = ['username', 'password']

class UserPasswordChangeSerializer(serializers.Serializer):
    old_password = serializers.CharField(label=_("Old Password"), max_length=20)
    new_password1 = serializers.CharField(label=_("New Password 1"), max_length=20)
    new_password2 = serializers.CharField(label=_("New Password 2"), max_length=20)

class UserImageSerializer(serializers.Serializer):
    image = serializers.ImageField(label=_("Avatar"))

class UserPairSerializer(serializers.Serializer):
    receiver = serializers.CharField(label=_("Receiver"))
