from django.urls import re_path

from . import consumers

websocket_urlpatterns = [
    re_path(r"ws/pong/(?P<room_name>\w+)/$", consumers.AsyncTestConsumer.as_asgi()),
]
