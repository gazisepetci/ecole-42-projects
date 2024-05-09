from django.core.exceptions import ValidationError, ObjectDoesNotExist
from django.db.models import UniqueConstraint
from django.db import models
from django.contrib.auth import get_user_model
from django.utils.translation import gettext_lazy as _
from django.utils import timezone
from datetime import timedelta

def max_player_validator(game_id):
    game = GameHistory.objects.get(pk=game_id)

    if game.player_count() >= game.max_players():
        raise ValidationError(_("Game #%(id)s is already full with maximum number of %(max)s players"),
                              params={"id": game_id, "max": game.max_players()})

def extract_query(history, target_user=None):
    games = list()

    for match in history:
        game = dict()
        
        game["id"] = match.pk
        game["date"] = match.date
        game["length"] = match.length
        game["type"] = GameHistory.GameType(match.type).name

        players = list()
        counter = 1

        for user in match.gamehistoryuser_set.all():
            player = dict()

            player["id"] = user.user.pk if user.user is not None else str("null")
            player["username"] = user.user.username if user.user is not None else str("[anonymous]")
            player["total_score"] = user.total_score
            player["wins"] = user.wins
            player["place"] = counter

            if target_user is not None and user.user is not None and user.user.pk == target_user:
                game["target_player"] = player

                if counter == 1:
                    game["target_player"]["has_won"] = True
                else:
                    game["target_player"]["has_won"] = False

            counter += 1
            players.append(player)

        game["players"] = players
        games.append(game)

    return games

class GameHistoryManager(models.Manager):

    def get_user_summary(self, user) -> dict:
        games = GameHistory.objects.prefetch_related('gamehistoryuser_set').filter(gamehistoryuser__user=user)

        onevsone = {'total': 0, 'wins': 0, 'losses': 0}
        tournament = {'total': 0, 'first': 0, 'second': 0, 'third': 0}

        for game in games:
            counter = 1
            for player in game.gamehistoryuser_set.all():
                if player.user == user:
                    if game.type == GameHistory.GameType.ONEVONE:
                        onevsone['total'] += 1
                        if counter == 1:
                            onevsone['wins'] += 1
                        else:
                            onevsone['losses'] += 1
                    else:
                        tournament['total'] += 1
                        if counter == 1:
                            tournament['first'] += 1
                        elif counter == 2:
                            tournament['second'] += 1
                        elif counter == 3:
                            tournament['third'] += 1
                counter += 1

        return {'onevsone': onevsone, 'tournament': tournament}

    def get_user_history(self, user_id, last=10):
        records = GameHistoryUser.objects.filter(user=user_id).order_by("-game__date")
        count = records.count()

        if last > count:
            records = records[0:count]
        else:
            records = records[0:last]

        return GameHistory.objects.filter(pk__in=records.values("game")).prefetch_related('gamehistoryuser_set')

    def get_user_best(self, user_id, last=3):
        records = GameHistoryUser.objects.filter(user=user_id).order_by("-wins", "-total_score")
        count = records.count()
        
        if last > count:
            records = records[0:count]
        else:
            records = records[0:last]

        return GameHistory.objects.filter(pk__in=records.values("game")).prefetch_related('gamehistoryuser_set')

    def get_ranking(self, last=10):
        records = GameHistoryUser.objects.order_by("-wins", "-total_score")
        count = records.count()

        if last > count:
            records = records[0:count]
        else:
            records = records[0:last]

        return GameHistory.objects.filter(pk__in=records.values("game")).prefetch_related('gamehistoryuser_set')

    def create_dummy_scores(self):
        if GameHistory.objects.count() != 0:
            return

        current_tz = timezone.get_current_timezone()
        
        self.game1 = GameHistory.objects.create(date=timezone.datetime(year=2010,
                                                                       month=1,
                                                                       day=1,
                                                                       tzinfo=current_tz),
                                                length=timedelta(minutes=5),
                                                type=GameHistory.GameType.ONEVONE)
        self.game2 = GameHistory.objects.create(date=timezone.now(),
                                                length=timedelta(seconds=30),
                                                type=GameHistory.GameType.TOURNAMENT)

        self.user1 = get_user_model().objects.create_user(username="user1", email="user1@mail.com", password="x")
        self.user2 = get_user_model().objects.create_user(username="user2", email="user2@mail.com", password="x")
        self.user3 = get_user_model().objects.create_user(username="user3", email="user3@mail.com", password="x")
        self.user4 = get_user_model().objects.create_user(username="user4", email="user4@mail.com", password="x")

        self.guser1_1 = GameHistoryUser.objects.create(game=self.game1, user=self.user1, total_score=25, wins=1)
        self.guser1_2 = GameHistoryUser.objects.create(game=self.game1, user=self.user2, total_score=10, wins=0)

        self.guser2_1 = GameHistoryUser.objects.create(game=self.game2, user=self.user1, total_score=200, wins=4)
        self.guser2_2 = GameHistoryUser.objects.create(game=self.game2, user=self.user2, total_score=185, wins=2)
        self.guser2_3 = GameHistoryUser.objects.create(game=self.game2, user=self.user3, total_score=32, wins=1)
        self.guser2_4 = GameHistoryUser.objects.create(game=self.game2, user=self.user4, total_score=50, wins=0)

        self.game3 = GameHistory.objects.create(date=timezone.now(),
                                                length=timedelta(hours=1),
                                                type=GameHistory.GameType.ONEVONE)
        self.game4 = GameHistory.objects.create(date=timezone.now(),
                                                length=timedelta(minutes=15),
                                                type=GameHistory.GameType.TOURNAMENT)

        GameHistoryUser.objects.create(game=self.game3, user=self.user1, total_score=15, wins=0)
        GameHistoryUser.objects.create(game=self.game4, user=self.user1, total_score=16, wins=1)
        GameHistoryUser.objects.create(game=self.game4, user=self.user2, total_score=17, wins=0)
        GameHistoryUser.objects.create(game=self.game4, user=self.user3, total_score=18, wins=0)

class GameHistory(models.Model):

    class Meta:
        verbose_name_plural = "game histories"
        ordering = ("-date",)

    class GameType(models.IntegerChoices):
        ONEVONE = 1, _("One vs One")
        TOURNAMENT = 2, _("Tournament")

        __empty__ = _("Unknown Game Type")

    type = models.IntegerField(choices=GameType)

    date = models.DateTimeField()
    length = models.DurationField()

    objects = GameHistoryManager()

    def player_count(self):
        return self.gamehistoryuser_set.count()

    def player_exists(self, user_id):
        return self.gamehistoryuser_set.filter(user=user_id).count() > 0

    def get_player_record(self, user_id):
        try:
            return self.gamehistoryuser_set.get(user=user_id)
        except ObjectDoesNotExist:
            return None

    def max_players(self):
        return 4 if self.type == self.GameType.TOURNAMENT else 2

class GameHistoryUser(models.Model):

    class Meta:
        constraints = [
            UniqueConstraint(fields=["game", "user"], name="history_user_index_constraint"),
        ]
        
        ordering = ("game", "-wins", "-total_score")

    game = models.ForeignKey(GameHistory, validators=[max_player_validator], on_delete=models.CASCADE)
    user = models.ForeignKey(get_user_model(), on_delete=models.SET_NULL, null=True)
    total_score = models.IntegerField()
    wins = models.IntegerField()

    def __str__(self):
        return self.user.username + "@" + str(self.game.type)
