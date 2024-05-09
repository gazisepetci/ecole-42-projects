import re

class Client:
    id_counter = 10

    def __init__(self, id, username, channel_name):
        self.id = id
        self.username = username
        self.channel_name = channel_name
        self.chatting = set()

    @classmethod
    def create(cls, username, channel_name):
        id = cls.id_counter
        cls.id_counter += 1
        return Client(id, username, channel_name)

    def add_chat(self, username):
        self.chatting.add(username)

    def remove_chat(self, username):
        self.chatting.discard(username)

    def __str__(self):
        return self.username

class ClientPool:
    #clients : dict[str, set[str]] = {} # username : list of chatting users
    #client_id : dict[str, int] = {} # username : unique_id # inefficient, better to get id from jwt
    clients : dict[str, Client] = {}
    rooms : dict[tuple[str, str], str] = {} # (user1, user2) : room_name & keep user1 < user2

    @classmethod
    def add_client(cls, username : str, channel_name) -> bool:
        if username in cls.clients:
            return False

        cls.clients[username] = Client.create(username, channel_name)
        return True

    @classmethod
    def add_room(cls, user1, user2) -> tuple[str, None] | tuple[None, str]: # room_name, reason
        pair = cls.get_pair(user1, user2)

        if pair in cls.rooms:
            return cls.rooms.get(pair, ""), None
            # return None, "Room already exists"

        cls.clients[user1].add_chat(user2)
        cls.clients[user2].add_chat(user1)

        room_name = "chat_" + str(cls.clients[user1].id) + "_" + str(cls.clients[user2].id)
        cls.rooms[pair] = room_name
        return room_name, None

    @classmethod
    def remove_client(cls, username : str):
        removed_client = cls.clients.pop(username, None)

        if removed_client is None:
            return

        for other in removed_client.chatting:
            if not other in cls.clients:
                cls.remove_room(username, other)

    @classmethod
    def remove_room(cls, user1 : str, user2 : str):
        room = cls.rooms.pop(cls.get_pair(user1, user2), None)

        if room is None:
            return

        if user1 in cls.clients:
            cls.clients[user1].remove_chat(user2)
        if user2 in cls.clients:
            cls.clients[user2].remove_chat(user1)

    @classmethod
    def is_online(cls, username):
        return username in cls.clients

    @classmethod
    def get_room(cls, user1, user2):
        return cls.rooms.get(cls.get_pair(user1, user2), None)

    @classmethod
    def get_channel_name(cls, username):
        client = cls.clients.get(username, None)

        if client is None:
            return None

        return client.channel_name

    @staticmethod
    def get_pair(user1 : str, user2 : str) -> tuple[str, str]:
        if user1 > user2:
            return (user2, user1)
        return (user1, user2)
