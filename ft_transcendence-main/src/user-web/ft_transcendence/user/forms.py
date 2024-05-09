from django.contrib.auth.forms import BaseUserCreationForm
from django.contrib.auth import get_user_model
from django import forms
from django.utils.translation import gettext_lazy as _

class UserLoginForm(forms.Form):
    username = forms.CharField(label=_("Username"), max_length=20, widget=forms.TextInput())
    password = forms.CharField(label=_("Password"), widget=forms.PasswordInput())

    class Meta:
        model = get_user_model()
        fields = ['username', 'password']

class UserPasswordChangeForm(forms.Form):
    old_password = forms.CharField(label=_("Old Password"), max_length=20, widget=forms.PasswordInput())
    new_password1 = forms.CharField(label=_("New Password 1"), max_length=20, widget=forms.PasswordInput())
    new_password2 = forms.CharField(label=_("New Password 2"), max_length=20, widget=forms.PasswordInput())

class UserRegistrationForm(BaseUserCreationForm):
    class Meta(BaseUserCreationForm.Meta):
        model = get_user_model()
        fields = BaseUserCreationForm.Meta.fields + ("email",)
