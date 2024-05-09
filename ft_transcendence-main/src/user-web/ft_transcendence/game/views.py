from datetime import timedelta
from django.contrib.auth import get_user_model
from django.shortcuts import render
from django.utils import timezone

from rest_framework.decorators import api_view
from rest_framework.parsers import JSONParser
from rest_framework.response import Response

from game import models

@api_view(['GET'])
def indexView(request):
	return render(request, 'game/index.html')

@api_view(['GET'])
def pongRoomView(request):
    return render(request, 'game/pong_room.html')

@api_view(['GET'])
def pongRoomLocalView(request):
    return render(request, 'game/pong_local.html')

@api_view(['POST'])
def registerGameView(request):
    data = JSONParser().parse(request)

    game = models.GameHistory.objects.create(type=data["game_type"],
                                               date=timezone.now(),
                                               length=timedelta(seconds=data["max_seconds"]),)

    for p in data["players"]:
        player = data["players"][p]
        user = get_user_model().objects.get(username=p)
        models.GameHistoryUser.objects.create(game=game,
                                                user=user,
                                                total_score=player["total_score"],
                                                wins=player["wins"])

    return Response({'message': 'Game data has been recorded'})
