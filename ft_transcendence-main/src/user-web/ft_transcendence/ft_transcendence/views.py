from django.shortcuts import render
from rest_framework.decorators import api_view

from user.models import UserRelationship

@api_view(['GET'])
def index(request):
    return render(request, "index.html") # index.html, index_test.html

@api_view(['GET'])
def home(request):
    context = {}
    if request.user.is_authenticated:
        context["incoming"] = UserRelationship.objects.incoming_requests_set(request.user)
        context["friends"] = UserRelationship.objects.friends_set(request.user)
    return render(request, "home.html", context)
