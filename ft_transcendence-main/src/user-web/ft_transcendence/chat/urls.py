from django.urls import path

from . import views

app_name = "chat"

urlpatterns = [
    path("", views.chatRoomView, name="chat-window"),
    path("test/", views.chatRoomView, name="chat-room"),
]
