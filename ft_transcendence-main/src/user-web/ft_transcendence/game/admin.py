from django.contrib import admin
from . import models

class GameHistoryUserInlıne(admin.TabularInline):
    model = models.GameHistoryUser
    can_delete = False
    readonly_fields = ("game", "user", "total_score", "wins")

    def has_add_permission(self, request, obj=None):
        return False

class GameHistoryAdmin(admin.ModelAdmin):
    list_display = ["id", "type", "date", "length"]
    inlines = [GameHistoryUserInlıne]

    def has_add_permission(self, request, obj=None):
        return False
    def has_change_permission(self, request, obj=None):
        return False
    def has_delete_permission(self, request, obj=None):
        return False

class GameHistoryUserAdmin(admin.ModelAdmin):
    def has_add_permission(self, request, obj=None):
        return False
    def has_change_permission(self, request, obj=None):
        return False
    def has_delete_permission(self, request, obj=None):
        return False

admin.site.register(models.GameHistory, GameHistoryAdmin)
admin.site.register(models.GameHistoryUser, GameHistoryUserAdmin)
