from channels.generic.websocket import WebsocketConsumer, AsyncWebsocketConsumer
from asgiref.sync import async_to_sync, sync_to_async

import json
import re
import asyncio

from pong.GameHandler import GamePool

class AsyncTestConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        """Accepts JWT authenticated users if the game room is not full"""

        self.room_name = self.scope["url_route"]["kwargs"]["room_name"]
        self.room_name = re.sub(r'\W+', '_', self.room_name)
        self.room_name = (self.room_name[:75]) if len(self.room_name) > 75 else self.room_name
        self.room_name = f"pong_{self.room_name}"

        self.username = self.scope.get("username", None)

        if self.username is None:
            await self.close()
            return

        created = GamePool().add_game(self.room_name)
        if not GamePool()[self.room_name].add_player(self.channel_name, self.username):
            self.username = None
            if created:
                GamePool().remove_game(self.room_name)
            await self.close()
            return

        await self.channel_layer.group_add(self.room_name, self.channel_name)

        if created:
            task = asyncio.create_task(GamePool().games[self.room_name].ping_loop(self.room_name))
            GamePool().games[self.room_name].task.add(task)
            task.add_done_callback(GamePool().games[self.room_name].task.discard)

        await self.accept()

    async def disconnect(self, close_code):
    
        if self.username is None:
            return

        if GamePool()[self.room_name].is_active():
            GamePool()[self.room_name].remove_channel(self.username)
        else:
            GamePool()[self.room_name].remove_player(self.username)

        if len(GamePool()[self.room_name]) < 1:
            GamePool().remove_game(self.room_name)

        await self.channel_layer.group_discard(self.room_name,
                                               self.channel_name)

    async def receive(self, text_data):
        text_data_json = json.loads(text_data)
        data = text_data_json
        data["room"] = self.room_name
        data["username"] = self.username
        data["type"] = text_data_json.get("type", "chat.message")

        if data["type"] == "chat.message":
            await self.channel_layer.group_send(self.room_name, data)
        else:
            await self.channel_layer.send(self.channel_name, data)

    async def pong_status(self, event):
        await self.send(text_data=json.dumps(event))

    async def pong_ready(self, event):
        username = event["username"]
        await GamePool()[self.room_name].toggle_ready(username)

    async def pong_move(self, event):
        username = event["username"]
        to_up = event.get("to_up", None)

        if to_up is not None and isinstance(to_up, bool):
            await GamePool()[self.room_name].move_player(username, to_up)

    async def pong_setting(self, event):
        username = event["username"]
        game = GamePool()[self.room_name]
        player = game[username]

        if player is not None and player.is_owner:
            game.update_settings(event["settings"])

    async def chat_message(self, event):
        username = event["username"]
        room = event["room"]
        prefix = username + "@" + room + ": "
        message = event["message"]

        await self.send(text_data=json.dumps({"type": "chat.message", "message": prefix + message}))

    async def chat_command(self, event):
        username = event["username"]
        room = event["room"]
        msg_prefix = username + "@" + room + ": "
        message = event["message"]
        info_prefix = "Pong: "
        info = "Unrecognized command"
        fields = message.split()
        game = GamePool()[self.room_name]
        player = game[username]

        if message.startswith("/games"):
            info = str(GamePool())

        elif message.startswith("/list"):
            if len(fields) == 1:
                info = str(game)
            else:
                info = ""
                for room in fields[1:]:
                    try:
                        info += room + ": " + str(GamePool()[room]) + "; "
                    except KeyError:
                        info += room + ": " + "None" + "; "

        elif message.startswith("/nick"):
            if len(fields) == 1:
                info = str(player.nickname if player is not None else "")
            else:
                if game.is_nick_unique(fields[1]):
                    player.set_nick(fields[1])
                    info = "nickname set to " + player.nickname
                else:
                    info = "someone else has already picked that nickname"

        elif message.startswith("/set"):
            if len(fields) != 3:
                info = "  Options: board_size (2), paddle_size (2), time_max (1), ball_radius (1), ball_velocity (2)\n \
                Example usage: \n\
                    \"/set board_size 500,200\"\n\
                    \"/set time_max 20\""
            elif not player.is_owner:
                info = "Only the room owner can update the settings."
            else:
                dims = []
                if fields[1] == "board_size" or fields[1] == "paddle_size" or fields[1] == "ball_velocity":
                    dims = fields[2].split(",")
                    if len(dims) != 2:
                        info = "Incorrect number of dimensions."
                if fields[1] == "board_size" and len(dims) == 2:
                    info = game.update_settings({'board_size': (dims[0], dims[1])})
                elif fields[1] == "paddle_size" and len(dims) == 2:
                    info = game.update_settings({'paddle_size': (dims[0], dims[1])})
                elif fields[1] == "ball_velocity" and len(dims) == 2:
                    info = game.update_settings({'ball_velocity': (dims[0], dims[1])})
                elif fields[1] == "time_max":
                    info = game.update_settings({'time_max': (fields[2])})
                elif fields[1] == "ball_radius":
                    info = game.update_settings({'ball_radius': (fields[2])})
                else:
                    info = "Incorrect option."

        elif message.startswith("/help"):
            info = "  games                : shows the list of all pong rooms\n\
            list (room_name)     : shows the list of users in current room or in room_name\n\
            nick <nickname>      : sets a new nickname if available\n\
            set <option> <value> : changes a parameter in the game, call \"/set\" to learn more about options\
            "
            
                
        response = msg_prefix + message + "\n" + info_prefix + info
        await self.send(text_data=json.dumps({"type": "chat.command", "message": response}))
