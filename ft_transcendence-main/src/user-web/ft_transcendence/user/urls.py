from django.urls import path
from rest_framework_simplejwt.views import TokenVerifyView, TokenRefreshView

from . import views

app_name = "user"

urlpatterns = [
    path("register/", views.RegisterView.as_view(), name="register"),
    path("login/", views.LoginView.as_view(), name="login"),
    path("logout/", views.logoutView, name="logout"),
    path("oauth-callback/", views.oauth_callback, name="oauth-callback"),
    path("get-oauth-url/", views.get_oauth_url, name="get-oauth-url"),
    path("verify-token/", TokenVerifyView.as_view(), name="token_verify"),
    # path("refresh-token/", TokenRefreshView.as_view(), name='token_refresh'),
    path("refresh-token/", views.refreshTokenView.as_view(), name="token_refresh"),
    path("friend-request/<str:target_username>/", views.FriendRequestView.as_view(), name="friend-request"),
    path("block-request/<str:target_username>/", views.UserBlockView.as_view(), name="block-request"),
    path("two-factor/", views.TwoFactorAuthenticationView.as_view(), name="two-factor"),

    path("profile/", views.profileView, name="profile"),
    path("profile/<int:target_id>/", views.profileView, name="target-profile"),

    path("change-password/", views.passwordChangeView, name="change-password"),
    path("delete-account/", views.deleteUserView, name="delete-account"),
    path("add-two-factor/<int:type>/", views.TwoFactorSettingView.as_view(), name="add-two-factor"),
    path("remove-two-factor/", views.TwoFactorSettingView.as_view(), name="remove-two-factor"),
    path("get_image/<int:user_id>/", views.UserImageView.as_view(), name="get-user-image"),
    path("get_image/", views.UserImageView.as_view(), name="get-user-image-2"),
    # =================
    #  Views for debug
    # =================
    path("check-session/", views.check_session, name="check-session"),
    path("check/", views.checkuser, name="user-check"),
    path("check2/", views.checkuser2, name="user-check2"),
    path("check3/", views.checkuser3, name="user-check3"),
    path("check4/", views.checkuser4, name="user-check4"),
    path("dummy/", views.dummyscores, name="dummy-scores"),
]
