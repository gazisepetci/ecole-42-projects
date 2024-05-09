from enum import IntEnum
from time import time

import random
import math
import asyncio
import copy
import requests
from operator import itemgetter

from pong.Vector import Vector2D

from channels.layers import get_channel_layer

class Player:
    def __init__(self, board_size : Vector2D, paddle_size : Vector2D,
                 nickname: str | None = None, velocity=5.0):
        self.nickname = nickname
        
        self.is_ready = False
        self.is_playing = False
        self.is_owner = False
        self.times_played = 0
        self.last_action = time()

        self.def_position = abs(Vector2D(board_size.x / 2 - paddle_size.x, 0))
        self.position = copy.copy(self.def_position)
        self.velocity = velocity

        self.score = 0
        self.total_score = 0
        self.wins = 0

    def reset_game_variables(self):
        """Reset variables while starting a match"""
        self.position = copy.copy(self.def_position)
        self.is_ready = False

    def toggle_position_x(self):
        self.position.x = -self.position.x

    def set_default_position(self, board_size : Vector2D, paddle_size : Vector2D):
        self.def_position = abs(Vector2D(board_size.x / 2 - paddle_size.x, 0))

    def move(self, to_up : bool, factor, player_margin):
        direction = 1 if to_up else -1

        tmp = self.position.y + direction * factor * self.velocity
        if abs(tmp) > player_margin.y:
            self.position.y = player_margin.y * direction
        else:
            self.position.y = tmp

    def set_nick(self, nickname):
        self.nickname = nickname

class Ball:
    def __init__(self, board_size: Vector2D, player_margin: Vector2D,
                 radius, velocity: tuple, position=(0.0,0.0)):

        self.def_position = Vector2D(position[0], position[1])
        self.def_velocity = abs(Vector2D(velocity[0], velocity[1]))
        self.position = copy.copy(self.def_position)
        self.velocity = copy.copy(self.def_velocity)

        self.radius = abs(radius)

        self.update_margin(board_size, player_margin)

    def update_margin(self, board_size, player_margin):
        self.bounce_margin = Vector2D(player_margin.x - self.radius,
                                      board_size.y / 2 - self.radius)
        self.score_marginx = player_margin.x

    def reset_game_variables(self):
        """Reset position and velocity to default"""
        self.position = copy.copy(self.def_position)
        self.velocity = copy.copy(self.def_velocity)

    def reset(self):
        """Reset ball and its direction based on last score"""
        pos_x = self.position.x
        self.reset_game_variables()

        if pos_x > 0:
            self.velocity.x = abs(self.velocity.x)
        else:
            self.velocity.x = -abs(self.velocity.x)

    def bounce_vertical(self) -> bool:
        if self.bounce_margin.y < abs(self.position.y):
            self.velocity.y = -self.velocity.y

        return True

    def bounce_horizontal(self, paddle_range: tuple[float, float]) -> bool:
        """Returns False if ball position has passed the paddle"""
        
        pos_x = abs(self.position.x)
        
        if self.bounce_margin.x < pos_x:

            if pos_x < self.score_marginx:
                if paddle_range[0] < self.position.y < paddle_range[1]:
                    if self.position.x > 0 and self.velocity.x > 0:
                        self.velocity.x = -self.velocity.x
                    elif self.position.x < 0 and self.velocity.x < 0:
                        self.velocity.x = -self.velocity.x
                return True
            else:
                return False
        
        return True

class GameState(IntEnum):
    PENDING = 1
    ACTIVE = 2
    LOOP_ENDED = 3
    FINISHED = 4
    STARTING = 5

class GameType(IntEnum):
    ONEVONE = 1
    TOURNAMENT = 2

class Game:
    def __init__(self,
                 board_size=(40,30), paddle_size=(2,6),
                 ball_radius=2.0, ball_velocity=(10.0, 5.0),
                 time_max = 15, type=GameType.ONEVONE):

        self.players : dict[str, Player] = {} # All players
        self.current_players = tuple() # 1V1 players when game is active
        self.next_players = tuple()
        self.channels = {} # Connected players
        self.status = GameState.PENDING
        self.time_started = time() # Dummy default
        self.time_elapsed = time() # Dummy default
        self.task = set()

        self.set_type(type)
        self.time_max = time_max

        self.board_size = abs(Vector2D(board_size[0], board_size[1]))
        self.paddle_size = abs(Vector2D(paddle_size[0], paddle_size[1]))
        self.update_player_margin(is_init=True)
        self.ball = Ball(self.board_size, self.player_margin,
                         radius=ball_radius, velocity=ball_velocity)

    def set_type(self, type : GameType):
        self.type = type
        if self.type == GameType.TOURNAMENT:
            self.max_players = 4
        else:
            self.max_players = 2

    def set_ball(self, radius, velocity):
        self.ball = Ball(self.board_size, self.player_margin,
                         radius=radius, velocity=velocity)

    def update_player_margin(self, is_init=False):
        self.player_margin = (self.board_size - self.paddle_size) * 0.5
        self.player_margin.x = self.board_size.x * 0.5 - self.paddle_size.x
        if not is_init:
            self.ball.update_margin(self.board_size, self.player_margin)
            for p in self.players:
                self.players[p].set_default_position(self.board_size, self.paddle_size)

    def add_player(self, channel_name, username, **kwargs) -> bool:
        if username in self.players and \
            username not in self.channels:
            self.channels[username] = channel_name
            return True
        elif len(self.players) >= self.max_players:
            return False
        elif GamePool().find_user(username) is None:
            player = Player(self.board_size, self.paddle_size,
                            nickname=username, **kwargs)
            if len(self.players) == 0:
                player.is_owner = True
            self.players[username] = player
            self.channels[username] = channel_name
            return True
        return False

    def remove_player(self, username: str) -> None | Player:
        self.remove_channel(username)
        if self.status == GameState.PENDING:
            return self.players.pop(username, None)
        return None

    def remove_channel(self, username : str):
        self.players[username].is_ready = False
        self.channels.pop(username, None)

    def is_nick_unique(self, nickname):
        for p in self.players:
            if self.players[p].nickname == nickname:
                return False
        return True

    def update_settings(self, settings):
        # if request from user who is_owner and game state is PENDING
        #   confirm settings has all required fields, then update

        if self.status == GameState.PENDING:
            try:
                for s in settings:
                    if s == "board_size":
                        board_size = tuple(float(n) for n in settings[s])
                        self.board_size = abs(Vector2D(board_size[0], board_size[1]))
                        self.update_player_margin()
                    elif s == "paddle_size":
                        paddle_size = tuple(float(n) for n in settings[s])
                        self.paddle_size = abs(Vector2D(paddle_size[0], paddle_size[1]))
                        self.update_player_margin()
                    elif s == "time_max":
                        self.time_max = int(settings[s])
                    elif s == "type":
                        gtype = GameType.TOURNAMENT if settings[s] == "TOURNAMENT" else GameType.ONEVONE
                        self.set_type(gtype)
                    elif s == "ball_radius":
                        rad = float(settings[s])
                        self.set_ball(radius=rad, velocity=self.ball.def_velocity)
                    elif s == "ball_velocity":
                        vel = tuple(float(n) for n in settings[s])
                        self.set_ball(radius=self.ball.radius, velocity=vel)

                return "Settings updated successfuly"
            except Exception as e:
                return str(e)
        else:
            return "The game is not in pending state"

    def is_active(self):
        return self.status == GameState.ACTIVE

    def is_all_ready(self):
        if len(self.players) == self.max_players or len(self.players) > 2:
            for user in self.players:
                if not self.players[user].is_ready:
                    return False
            return True
        return False

    def full_reset(self):
        self.ball.reset_game_variables()
        for user in self.players:
            self.players[user].reset_game_variables()
            self.players[user].total_score = 0
            self.players[user].wins = 0
            self.players[user].times_played = 0

    async def toggle_ready(self, username):
        if self.status != GameState.PENDING:
            return

        self.players[username].is_ready = not self.players[username].is_ready

        if self.is_all_ready():
            task = asyncio.create_task(self.startGame())
            self.task.add(task)
            task.add_done_callback(self.task.discard)

    async def ping_loop(self, room_name):
        channel_layer = get_channel_layer()

        while not (len(self.channels) == 0 and self.status == GameState.PENDING):
            if len(self.channels) > 0:
                await channel_layer.group_send(room_name, self.get_ping_dict())
                await asyncio.sleep(30e-3) # 25ms

    def get_ping_dict(self):

        ball_data = {
            "pos_x": self.ball.position.x,
            "pos_y": self.ball.position.y,
            "vel_x": self.ball.velocity.x,
            "vel_y": self.ball.velocity.y,
            "radius": self.ball.radius
        }

        players = {}

        for p in self.players:
            user = self.players[p]
            players[p] = {
                "nickname": user.nickname if user.nickname is not None else p,
                "is_ready": user.is_ready,
                "is_playing": user.is_playing,
                "is_owner": user.is_owner,
                "pos_x": user.position.x,
                "pos_y": user.position.y,
                "vel": user.velocity,
                "score": user.score,
                "total_score": user.total_score,
                "wins": user.wins,
            }

        data = {
            "status": self.status,
            "game_type": self.type,
            "max_players": self.max_players,
            "ball": ball_data,
            "board_size": (self.board_size.x, self.board_size.y),
            "paddle_size": (self.paddle_size.x, self.paddle_size.y),
            "players": players,
            "current_players": self.current_players,
            "next_players": self.next_players,
            "seconds": self.time_elapsed - self.time_started,
            "max_seconds": self.time_max,
        }

        data["type"] = "pong.status"

        return data

    async def move_player(self, username, to_up : bool):
        now = time()
        t_delta = now - self.players[username].last_action

        if t_delta > 10e-3: # 5ms
            self.players[username].move(to_up, 0.1, self.player_margin)
            self.players[username].last_action = now


    def __str__(self):
        return str([username for username in self.players])

    def __getitem__(self, username: str) -> None | Player:
        try:
            return self.players[username]
        except KeyError:
            return None

    def __len__(self):
        return len(self.channels)

    def pair_select(self, pl_list, loop_count) -> tuple[None | tuple[str, ...], None | tuple[str, ...]]: 
        # match players with lowest number of times_played and wins
        
        if loop_count >= self.max_players or len(pl_list) == 0:
            return None, None
        
        pair : list[str] = list()
        select = len(pl_list) if len(pl_list) < 2 else 2
        pl_tuples = [(p, self.players[p].times_played, self.players[p].wins) for p in pl_list]

        if loop_count < math.floor(self.max_players / 2):
            pl_tuples = sorted(pl_tuples, key=itemgetter(2)) # sort by wins
            pl_tuples = sorted(pl_tuples, key=itemgetter(1)) # sort by times_played
            # primary key times_played, secondary key wins
            pair = [pl_tuple[0] for pl_tuple in pl_tuples[0:select]]
        elif loop_count != self.max_players - 1:
            pl_tuples = sorted(pl_tuples, key=itemgetter(1)) # sort by times_player
            pl_tuples = sorted(pl_tuples, key=itemgetter(2)) # sort by wins
            # primary key wins, secondary key times_played
            pair = [pl_tuple[0] for pl_tuple in pl_tuples[0:select]]
        else:
            pl_tuples = sorted(pl_tuples, key=itemgetter(1)) # sort by times_player
            pl_tuples = sorted(pl_tuples, key=itemgetter(2)) # sort by wins
            # primary key wins, secondary key times_played
            pair = [pl_tuple[0] for pl_tuple in pl_tuples[-select::]]

        diff = [x for x in pl_list if x not in pair]
        next, _ = self.pair_select(diff, loop_count + 1)
        random.shuffle(pair)
        return (tuple(pair), next)

    def paddle_range(self, players) -> tuple[float, float]:
        if self.ball.position.x > 0:
            min = self.players[players[1]].position.y - self.paddle_size.y / 2
            max = self.players[players[1]].position.y + self.paddle_size.y / 2
        else:
            min = self.players[players[0]].position.y - self.paddle_size.y / 2
            max = self.players[players[0]].position.y + self.paddle_size.y / 2

        return (min, max)
    
    def set_score(self, players):
        if self.ball.position.x > 0:
            self.players[players[0]].score += 1
        else:
            self.players[players[1]].score += 1

        self.ball.reset()

    async def startGame(self):
        pl_list = list(self.players)
        random.shuffle(pl_list)
        self.full_reset()

        if self.type == GameType.ONEVONE:
            await self.startMatch((pl_list[0], pl_list[1]))
        else:
            loop_count = 0
            while loop_count < self.max_players:
                pair, next = self.pair_select(pl_list, loop_count)
                if next is None:
                    self.next_players = tuple()
                elif len(next) == 1:
                    if loop_count < math.floor(self.max_players / 2):
                        self.next_players = (next[0], "[loser]")
                    else:
                        self.next_players = (next[0], "[winner]")
                else:
                    self.next_players = next
                if pair is not None and len(pair) == 2:
                    await self.startMatch(pair)
                else:
                    raise PairNotFound()
                loop_count += 1
        
        self.status = GameState.FINISHED
        # Send game data to database
        r = requests.post('http://user-web:8002/game/register/', json=self.get_ping_dict())
        await asyncio.sleep(10)
        self.status = GameState.PENDING

        print("GAME FINISHED") # DEBUG

    async def startMatch(self, players : tuple[str, str]):
        self.current_players = players
        for p in players:
            self.players[p].reset_game_variables()
            self.players[p].is_playing = True
            self.players[p].score = 0
        self.players[players[0]].toggle_position_x()
        self.status = GameState.STARTING
        await asyncio.sleep(4)
        self.status = GameState.ACTIVE
        self.time_started = time()
        self.time_elapsed = self.time_started

        while (self.status != GameState.LOOP_ENDED):
            await self.cycle(players)
            if self.time_elapsed - self.time_started > self.time_max \
                and self.players[players[0]].score != self.players[players[1]].score:
                self.status = GameState.LOOP_ENDED
            await asyncio.sleep(20e-3) # 25ms

        await asyncio.sleep(3)

        for p in players:
            self.players[p].times_played += 1
            self.players[p].is_playing = False
            self.players[p].total_score += self.players[p].score

        if self.players[players[0]].score > self.players[players[1]].score:
            self.players[players[0]].wins += 1
        elif self.players[players[0]].score < self.players[players[1]].score:
            self.players[players[1]].wins += 1

        self.current_players = ()

    async def cycle(self, players):
        t_delta = time() - self.time_elapsed

        if t_delta > 10e-3: # 10ms

            self.ball.bounce_vertical()
            if not self.ball.bounce_horizontal(self.paddle_range(players)):
                self.set_score(players)

            self.ball.position.x += self.ball.velocity.x * t_delta
            self.ball.position.y += self.ball.velocity.y * t_delta

        self.time_elapsed = time()

class GamePool:
    games : dict[str, Game] = {}

    @classmethod
    def add_game(cls, room_name: str, **kwargs) -> bool:
        if room_name not in cls.games:
            game = Game(**kwargs)
            cls.games[room_name] = game
            return True
        return False

    @classmethod
    def remove_game(cls, room_name: str) -> None | Game:
        return cls.games.pop(room_name, None)

    @classmethod
    def find_user(cls, username: str) -> None | str:
        """Returns room_name of the game where the user with username exists"""
        for room_name in cls.games:
            if cls.games[room_name][username] is not None:
                return room_name
        return None

    @classmethod
    def __str__(cls):
        return str([room for room in cls.games])

    @classmethod
    def __getitem__(cls, room_name: str) -> Game:
        return cls.games[room_name]

class PairNotFound(Exception):
    pass
