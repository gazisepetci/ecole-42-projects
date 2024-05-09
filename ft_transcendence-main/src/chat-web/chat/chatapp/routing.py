from django.urls import re_path, path

from . import consumers

websocket_urlpatterns = [
    path("ws/chat-api/", consumers.AsyncChatConsumer.as_asgi()),
]
