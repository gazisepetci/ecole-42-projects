from django.urls import path
from rest_framework_simplejwt.views import TokenVerifyView

urlpatterns = [
    path("verify-token/", TokenVerifyView.as_view(), name="token_verify"),
]
