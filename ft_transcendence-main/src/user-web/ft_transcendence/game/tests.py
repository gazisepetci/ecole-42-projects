from django.contrib.auth import get_user_model
from django.test import TestCase
from django.utils import timezone
from game.models import GameHistory, GameHistoryUser

from datetime import timedelta

class GameHistoryTestCase(TestCase):
    def setUp(self):
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

    def test_player_count(self):
        """Test if the number of players in a game are correctly counted"""

        self.assertEqual(self.game1.player_count(), 2)
        self.assertEqual(self.game2.player_count(), 4)
        self.assertEqual(self.game3.player_count(), 1)
        self.assertEqual(self.game4.player_count(), 3)

    def test_max_player_count(self):
        """Test if the maximum number of players are correct according to game type"""
        
        self.assertEqual(self.game1.max_players(), 2)
        self.assertEqual(self.game2.max_players(), 4)
        self.assertEqual(self.game3.max_players(), 2)
        self.assertEqual(self.game4.max_players(), 4)

    def test_player_exists(self):
        """Test if player_exists correctly finds a registered player in a game"""
        
        self.assertIs(self.game1.player_exists(self.user1.pk), True)
        self.assertIs(self.game1.player_exists(self.user2.pk), True)
        self.assertIs(self.game1.player_exists(self.user3.pk), False)

    def test_get_player_record(self):
        """Test if get_player_record returns a registered player object in a game"""

        self.assertEqual(self.game1.get_player_record(self.user1.pk).user.pk, self.user1.pk)
        self.assertEqual(self.game1.get_player_record(self.user2.pk).user.pk, self.user2.pk)
        self.assertIs(self.game1.get_player_record(self.user3.pk), None)

    def test_manager_user_history(self):
        """Test if user history is retrieved in correct date order"""

        records = GameHistory.objects.get_user_history(self.user1.pk)
        counts = records.count()

        for i in range(0, counts - 1):
            self.assertIs(records[i].player_exists(self.user1.pk), True)
            self.assertGreaterEqual(records[i].date, records[i + 1].date)

    def test_manager_user_best(self):
        """Test if user best records is retrieved in correct win and score order"""

        records = GameHistory.objects.get_user_best(self.user1.pk)
        counts = records.count()

        for i in range(0, counts - 1):
            user_record = records[i].get_player_record(self.user1.pk)

            win0 = user_record.wins
            win1 = user_record.wins
            score0 = user_record.total_score
            score1 = user_record.total_score

            self.assertGreaterEqual(win0, win1)
            
            if win0 == win1:
                self.assertGreaterEqual(score0, score1)
