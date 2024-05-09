from django.http import JsonResponse, HttpResponse, Http404, FileResponse

from django.db.models import Q
from django.contrib.auth import logout, authenticate, login, get_user_model
from django.contrib import messages
from django.shortcuts import get_object_or_404, render, HttpResponseRedirect, reverse
from django.conf import settings
from django.utils.translation import gettext_lazy as _
from django.views import View
from django.utils.decorators import method_decorator
from django.views.decorators.http import require_GET
from django.views.decorators.csrf import ensure_csrf_cookie
from django.core.files.images import ImageFile

from rest_framework.decorators import api_view, permission_classes
from rest_framework.exceptions import AuthenticationFailed
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from rest_framework.parsers import JSONParser
from rest_framework.views import APIView
from rest_framework import status

from rest_framework_simplejwt.tokens import RefreshToken
from rest_framework_simplejwt.serializers import TokenRefreshSerializer
from django_otp.forms import OTPTokenForm
from django_otp.plugins.otp_email.models import EmailDevice

import json
import logging # is this necessary?
import requests # is this necessary?
import os
from tempfile import NamedTemporaryFile

from . import forms
from . import serializers
from user.models import UserRelationship
from game.models import GameHistory, extract_query

TOKEN_URL = "https://api.intra.42.fr/oauth/token"
AUTHORIZATION_URL = "https://api.intra.42.fr/oauth/authorize"

logger = logging.getLogger(__name__)

class RegisterView(APIView):

    def get(self, request):
        context = {'form': forms.UserRegistrationForm().render("user/form_snippet.html")}
        return render(request, "user/register.html", context)

    def post(self, request):

        data = json.loads(request.body)
        form = forms.UserRegistrationForm(data=data)

        if form.is_valid():
            try:
                user = form.save()
            except ValueError as e:
                return Response({'success': False, "message": "ValueError", "errors": e.args}, status=400)
            except:
                return Response({'success': False, "message": _("An error occured while registering user in the database")},
                                    status=507)
            return Response({'success': True, "redirect": reverse("user:login"), "message": _("Successfully registered")})

        else:
            password1 = form.data.get("password1", None)
            password2 = form.data.get("password2", None)
            username = form.data.get("username", None)
            email = form.data.get("email", None)

            errors = []

            for error in form.errors:
                if form.data.get(error, None) is None:
                    errors.append(_(error + " field is not found"))
                elif error == 'email':
                    if get_user_model().objects.filter(email=email).exists():
                        errors.append(_("Email is already taken"))
                    else:
                        errors.append(_("Invalid email"))
                elif error == 'password2' and password1 == password2:
                    errors.append(_("The password is not strong enough"))
                elif error == 'password2' and password1 != password2:
                    errors.append(_("The passwords do not match"))
                elif error == 'username':
                    if get_user_model().objects.filter(username=username).exists():
                        errors.append(_("Username is already taken"))
                    else:
                        errors.append(_("Invalid username" + error))
                else:
                    errors.append(_("Invalid form error: " + error))
            return Response({'success': False, 'errors': errors}, status=401)

class LoginView(APIView):
    def get(self, request):
        if not request.user.is_authenticated:
            form = forms.UserLoginForm().render("user/form_snippet.html")
            return render(request, "user/login.html", {'form': form})
        else:
            return HttpResponseRedirect(reverse("home"))

    def post(self, request):
        data = JSONParser().parse(request)
        serializer = serializers.UserLoginSerializer(data=data)

        if serializer.is_valid():
            username = serializer.validated_data['username']
            password = serializer.validated_data['password']
            user = authenticate(request, username=username, password=password)

            if user is not None:
                if user.two_fa_auth_type == get_user_model().TwoFAType.NONE:
                    refresh = RefreshToken.for_user(user)
                    response_data = {'success': True,
                                     'redirect': reverse('home'),
                                     'message': _("login successful"),
                                     }
                    response = Response(response_data)
                    response.set_cookie('refresh_token', str(refresh), secure=True, samesite='Strict', httponly=True)
                    response.set_cookie('access_token', str(refresh.access_token), secure=True, samesite='Strict')
                    response.set_cookie('username', str(username), secure=True, samesite='Strict')
                    return response
                else:
                    request.session["attempting_user"] = user.id
                    response = {'success': True,
                                'redirect': reverse('user:two-factor'),
                                'message': _("Login successful")}
                    return Response(response)
            else:
                response = {'success': False, 'errors': [_("Incorrect username or password")]}
                return Response(response, status=status.HTTP_401_UNAUTHORIZED)
        else:
            # for error in serializer.errors:
            #    messages.error(request, "Invalid Serializer:" + error)
            response = {'success': False, 'errors': serializer.errors}
            return Response(response, status=status.HTTP_401_UNAUTHORIZED)

@api_view(['GET'])
def logoutView(request):
    if request.session.get("attempting_user", None) is not None:
        request.session.pop("attempting_user")
    response = Response({'success': True, 'redirect': reverse('home'),
                         'message': _("User is logged out")})
    response.delete_cookie('refresh_token', samesite='Strict')
    response.delete_cookie('access_token', samesite='Strict')
    response.delete_cookie('username', samesite='Strict')
    return response

@api_view(['GET'])
@permission_classes([IsAuthenticated])
def profileView(request, target_id = None):

    if target_id is None:
        user = request.user
    else:
        user = get_object_or_404(get_user_model(), id=target_id)

    history = extract_query(GameHistory.objects.get_user_history(user.pk), user.pk)
    relationship = UserRelationship.objects.get_type(request.user, user)
    summary = GameHistory.objects.get_user_summary(user)
    context = {"target_user" : user, "ranking": history,
               "relationship": relationship, "summary": summary}
    return render(request, "user/profile.html", context)


class refreshTokenView(APIView):
    def post(self, request):
        data = JSONParser().parse(request)
        serializer = TokenRefreshSerializer(data=data)

        if serializer.is_valid():
            access = serializer.validated_data['access']
            response = Response({'success': True, 'message': _("Refreshed access token")})
            response.set_cookie('access_token', access, secure=True, samesite='Strict')
            return response
        else:
            if request.session.get("attempting_user", None) is not None:
                request.session.pop("attempting_user")
            response = Response({'success': False, 'errors': [_("Invalid refresh token")]},
                                status=status.HTTP_401_UNAUTHORIZED)
            response.delete_cookie('refresh_token', samesite='Strict')
            response.delete_cookie('access_token', samesite='Strict')
            response.delete_cookie('username', samesite='Strict')
            return response
    def get(self, request):
        refresh_token = request.COOKIES.get("refresh_token")
        if refresh_token is None:
            return Response({'success': False,
                             'errors': [_("Refresh token not found in cookies")]},
                            status=status.HTTP_400_BAD_REQUEST)

        serializer = TokenRefreshSerializer(data={"refresh": refresh_token})

        if serializer.is_valid():
            access = serializer.validated_data['access']
            response = Response({'success': True, 'message': _("Refreshed access token")})
            response.set_cookie('access_token', access, secure=True, samesite='Strict')
            return response
        else:
            response = Response({'success': False, 'errors': [_("Invalid refresh token")]},
                                status=status.HTTP_401_UNAUTHORIZED)
            response.delete_cookie('refresh_token', samesite='Strict')
            response.delete_cookie('access_token', samesite='Strict')
            response.delete_cookie('username', samesite='Strict')
            return response

def get_oauth_url(request):
    oauth_url = f"{AUTHORIZATION_URL}?client_id={settings.OAUTH_CLIENT_ID}&redirect_uri={settings.OAUTH_REDIRECT_URI}&response_type=code"
    return JsonResponse({'oauth_url': oauth_url, 'redirect': reverse('home')})

@api_view(['GET', 'POST'])
def oauth_callback(request):
    code = request.GET.get('code')
    if code:
        token_response = requests.post(TOKEN_URL, data={
            'grant_type': 'authorization_code',
            'client_id': settings.OAUTH_CLIENT_ID,
            'client_secret': settings.OAUTH_CLIENT_SECRET,
            'code': code,
            'redirect_uri': settings.OAUTH_REDIRECT_URI,
        }).json()

        access_token = token_response.get("access_token")
        if access_token:
            user_info = requests.get('https://api.intra.42.fr/v2/me', headers={'Authorization': f'Bearer {access_token}'}).json()

			#TODO: Check if access_token is valid

            user, created = get_user_model().objects.get_or_create(
                username=user_info.get('login'),
                defaults={'email': user_info.get('email'),
                          'is_42authenticated': True,
				}
            )
            if created:
                image_url = user_info.get('image', {}).get('link')
                img = NamedTemporaryFile(delete=True)
                response = requests.get(image_url)
                img.write(response.content)
                img.flush()
                user.image.save(os.path.basename(image_url), ImageFile(img), save=True)
                user.set_unusable_password()
                user.save()

            refresh = RefreshToken.for_user(user)
            response_data = {'success': True,
                             'redirect': reverse('home'),
                             'message': _("login successful"),
                             #'refresh': str(refresh),
                             #'access': str(refresh.access_token)
                             }
            response = Response(response_data)
            response.set_cookie('refresh_token', str(refresh), secure=True, samesite='Strict', httponly=True)
            response.set_cookie('access_token', str(refresh.access_token), secure=True, samesite='Strict')
            response.set_cookie('username', str(user.username), secure=True, samesite='Strict')
            return response
        else:
            response = {'success': False, 'message': _("Incorrect access token")}
            return Response(response, status=status.HTTP_401_UNAUTHORIZED)
    response = {'success': False, 'message': _("Invalid login request")}
    return Response(response, status=status.HTTP_400_BAD_REQUEST)

@api_view(['GET'])
def check_session(request):
    is_logged_in = request.user.is_authenticated
    return Response({'isLoggedIn': is_logged_in})

class FriendRequestView(APIView):

    permission_classes = [IsAuthenticated]

    def put(self, request, target_username):
        sender = request.user
        receiver = get_object_or_404(get_user_model(), username=target_username)
        success = UserRelationship.objects.add_friend(sender, receiver)
        if success:
            return Response({'success': True, 'message': _('User add/accept friend request is successful')})
        else:
            return Response({'success': False, 'errors': [_('Cannot add user as friend')]})

    def delete(self, request, target_username):
        sender = request.user
        receiver = get_object_or_404(get_user_model(), username=target_username)
        success = UserRelationship.objects.remove_friend(sender, receiver)
        if success:
            return Response({'success': True, 'message': _('User has been removed from friends')})
        else:
            return Response({'success': False, 'errors': [_('Cannot remove user from friends')]})

class UserBlockView(APIView):

    permission_classes = [IsAuthenticated]

    def put(self, request, target_username):
        sender = request.user
        receiver = get_object_or_404(get_user_model(), username=target_username)
        success = UserRelationship.objects.block_user(sender, receiver)
        if success:
            return Response({'success': True, 'message': _('User has been blocked')})
        else:
            return Response({'success': False, 'errors': [_('Cannot block user')]})

    def delete(self, request, target_username):
        sender = request.user
        receiver = get_object_or_404(get_user_model(), username=target_username)
        success = UserRelationship.objects.unblock_user(sender, receiver)
        if success:
            return Response({'success': True, 'message': _('User has been unblocked')})
        else:
            return Response({'success': False, 'errors': [_('Cannot unblock user')]})

class TwoFactorAuthenticationView(APIView):
    def get(self, request):
        user_id = request.session.get("attempting_user", None)
        if user_id is None:
            return render(request, "error.html", {'error': "Unauthorized Request"}, status=401)
        else:
            user = get_object_or_404(get_user_model(), id=user_id)
            if user.two_fa_auth_type == get_user_model().TwoFAType.EMAIL:
                device = get_object_or_404(EmailDevice, user=user)
                device.generate_challenge()
            elif user.two_fa_auth_type == get_user_model().TwoFAType.TOTP:
                pass
            else:
                return HttpResponse("No two-factor authentication device registered for the user #" + str(user_id), status=401)

            form = OTPTokenForm(user).render("user/2fa_snippet.html")
            context = {'form': form}
            return render(request, "user/two-factor.html", context)
    def post(self, request):
        user_id = request.session.get("attempting_user", None)
        if user_id is None:
            return render(request, "error.html", {'error': "Unauthorized Request"}, status=401)
        else:
            user = get_object_or_404(get_user_model(), id=user_id)
            data = json.loads(request.body)
            form = OTPTokenForm(user, data=data)

            if form.is_valid():
                refresh = RefreshToken.for_user(user)
                response_data = {'success': True,
                                 'redirect': reverse('home'),
                                 'message': _("Login successful")}
                response = Response(response_data)
                response.set_cookie('refresh_token', str(refresh), secure=True, samesite='Strict', httponly=True)
                response.set_cookie('access_token', str(refresh.access_token), secure=True, samesite='Strict')
                return response
            else:
                return Response({'success': False, 'errors': [form.errors["__all__"]]}, status=status.HTTP_401_UNAUTHORIZED)


@api_view(['PUT'])
@permission_classes([IsAuthenticated])
def passwordChangeView(request):
    data = JSONParser().parse(request)
    response = {'success': False, 'errors': []}
    serializer = serializers.UserPasswordChangeSerializer(data=data)

    if serializer.is_valid():
        if not request.user.has_usable_password() \
            or request.user.check_password(serializer.validated_data['old_password']):
            p1 = serializer.validated_data['new_password1']
            p2 = serializer.validated_data['new_password2']

            if p1 != p2:
                response['errors'].append(_("Passwords do not match"))
                return Response(response, status=status.HTTP_400_BAD_REQUEST)
            request.user.set_password(p1)
            request.user.save()
            response['success'] = True
            response['message'] = _("Password change is successful")
            return Response(response)
        else:
            response['errors'].append(_("Invalid password"))
            return Response(response, status=status.HTTP_401_UNAUTHORIZED)

    else:
        response['errors'].append(_("Invalid data"))
        return Response(response, status=status.HTTP_401_UNAUTHORIZED)

@api_view(['DELETE'])
@permission_classes([IsAuthenticated])
def deleteUserView(request):
    response = HttpResponseRedirect(reverse('home'))
    response.delete_cookie('refresh_token', samesite='Strict')
    response.delete_cookie('access_token', samesite='Strict')
    request.user.delete()
    return response

class TwoFactorSettingView(APIView):
    permission_classes = [IsAuthenticated]

    def put(self, request, type):
        try:
            device = request.user.register_otp_device(type)
        except Exception as e:
            return Response({'success': False,
                             'message': _('Cannot set an OTP device'),
                             'errors': [str(e)]})

        response_data = {'success': True, 'message': _('Successfuly set OTP device')}

        if type == get_user_model().TwoFAType.TOTP:
            response_data["secret"] = device.config_url

        return Response(response_data)

    def delete(self, request):
        try:
            request.user.remove_otp_device()
            return Response({'success': True, 'message': _('Successfuly removed the OTP device')})
        except Exception as e:
            return Response({'success': False, 'message': _('Cannot remove any OTP device'),
                             'errors': [str(e)]})

class UserImageView(APIView):
    def get(self, request, user_id=None):
        # Varsayılan resim yolu
        default_image_path = os.path.join(settings.MEDIA_ROOT, 'image/default/user.png')

        if user_id is None:
            image_path = request.user.image.path
        else:
            try:
                user = get_user_model().objects.get(pk=user_id)
                image_path = user.image.path
            except get_user_model().DoesNotExist:
                image_path = default_image_path

        if os.path.exists(image_path):
            return FileResponse(open(image_path, 'rb'))
        else:
            return HttpResponse(status=status.HTTP_404_NOT_FOUND)

    def put(self, request):
        if not request.user.is_authenticated:
            return Response({"success": False, "errors": ["Unauthenticated user"]}, status=status.HTTP_403_FORBIDDEN)

        # JSONParser'ı kullanarak gelen veriyi ayrıştır
        serializer = serializers.UserImageSerializer(data=request.data)

        if serializer.is_valid():
            # Eski resmi silmek için güvenli kontrol
            old_image_path = request.user.image.path
            default_image_path = os.path.join(settings.MEDIA_ROOT, 'image/default/user.png')

            if old_image_path != default_image_path:
                try:
                    if os.path.exists(old_image_path):
                        os.remove(old_image_path)
                except Exception as e:
                    return Response({"success": False, "errors": [str(e)]}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

            request.user.image = serializer.validated_data['image']
            request.user.save()
            return Response({"success": True, "message": "Successfully updated user image"}, status=status.HTTP_200_OK)
        else:
            return Response({"success": False, "errors": serializer.errors}, status=status.HTTP_400_BAD_REQUEST)


# =================
#  Views for debug
# =================

@require_GET # Uses default session-based Django authentication
def checkuser(request):
    if request.user.is_authenticated:
        return HttpResponse("request.user.is_authenticated\n request.user.username: " + str(request.user.username))
    else:
        return HttpResponse("NOT request.user.is_authenticated\n request.user.username: " + str(request.user.username), status="401")

@api_view(['GET']) # Restricted view for DRF authentication
@permission_classes([IsAuthenticated])
def checkuser2(request):
    return HttpResponse("You are authenticated\n request.user.username: " + str(request.user.username))

@api_view(['GET']) # Different responses for (un)authenticated requests
def checkuser3(request):
    if request.auth:
        return HttpResponse("You are authenticated\n request.user.username: " + str(request.user.username))
    else:
        return HttpResponse("You are NOT authenticated\n request.user.username: " + str(request.user.username), status="401")

@api_view(['GET'])
def checkuser4(request):
    if request.user.is_authenticated:
        return HttpResponse("request.user.is_authenticated\n request.user.username: " + str(request.user.username))
    else:
        return HttpResponse("NOT request.user.is_authenticated\n request.user.username: " + str(request.user.username), status="401")

@api_view(['PUT'])
def dummyscores(request):
    GameHistory.objects.create_dummy_scores()
    return HttpResponse()
