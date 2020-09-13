"""mysite URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, include
from mysiteapp import views

urlpatterns = [
	path("admin/", admin.site.urls),
	path("", views.movie_list),
	path("movie_list/", views.movie_list),
	path("movie/<int:movie_id>", views.movie),
	path("actor_list/", views.actor_list),
	path("actor/<int:actor_id>", views.actor),
	path("search_result/", views.search_result)
]
