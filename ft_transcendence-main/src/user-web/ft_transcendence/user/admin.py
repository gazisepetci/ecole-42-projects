from django.contrib import admin
from . import models

class UserRelationshipAdmin(admin.ModelAdmin):
    list_display = ("user1", "user2", "type")

admin.site.register(models.User)
admin.site.register(models.UserRelationship, UserRelationshipAdmin)
