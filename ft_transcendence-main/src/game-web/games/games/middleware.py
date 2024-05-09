import http.cookies
from random import randint

from rest_framework_simplejwt.tokens import AccessToken
from rest_framework_simplejwt.exceptions import TokenError

class JWTAuthMiddleware:
    """Custom middleware that validates access_token cookie via rest_framework_simplejwt
    scope.username is populated with the username retrieved from a valid access token
    access_token is expected to include a "username" field
    """

    def __init__(self, app):
        self.app = app

    async def __call__(self, scope, receive, send):
        
        headers = { k.decode('ascii'):v.decode('ascii') for k,v in scope["headers"] }
       
        if headers.get("cookie", None) is not None:

            cookie = http.cookies.SimpleCookie()
            cookie.load(headers["cookie"])
            
            cookie_dict = { k:v.value for k,v in cookie.items() }

            access_token = cookie_dict.get("access_token", None)

            if access_token is not None:
                try:
                    token = AccessToken(access_token)
                    username = token.get("username", None)
                    if username is not None:
                        scope["username"] = username
                except TokenError as e:
                    print(e) # DEBUG
        
        return await self.app(scope, receive, send)
