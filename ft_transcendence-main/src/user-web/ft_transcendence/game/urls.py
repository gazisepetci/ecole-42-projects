from django.urls import path

from . import views

app_name = "game"

urlpatterns = [
    path("", views.indexView, name="index"),
    path("pong/", views.pongRoomView, name="pong"),
    path("pong-local/", views.pongRoomLocalView, name="pong-local"),
    path("register/", views.registerGameView, name="register"),
]
