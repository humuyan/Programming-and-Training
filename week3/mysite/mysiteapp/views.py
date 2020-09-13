from django.http import HttpResponse
from django.shortcuts import render
from mysiteapp.models import ActorModel, MovieModel, CommentModel
from django.core.paginator import Paginator
from django.db.models import Q
import time
import math


def paginator_list(current_page, total_pages):
	if total_pages == 0:
		return []
	ret = [1]
	if current_page > 4:
		ret.append(0)
	for i in range(max(current_page - 2, 2), min(current_page + 3, total_pages)):
		ret.append(i)
	if current_page + 3 < total_pages:
		ret.append(0)
	if total_pages != 1:
		ret.append(total_pages)
	return ret


def movie_list(request):
	page = 1 if not request.GET.get("page") else int(request.GET.get("page"))
	total_list = list(MovieModel.objects.all())
	p = Paginator(total_list, 12)
	item_list = p.page(page).object_list
	return render(
		request,
		"movie_list.html",
		{"movies": item_list, "paginator": paginator_list(page, math.ceil(len(total_list) / 12))}
	)


def movie(request, movie_id):
	return render(
		request,
		"movie.html",
		{
			"movie": MovieModel.objects.filter(movieID=movie_id)[0],
			"comments": CommentModel.objects.filter(movie__movieID=movie_id)
		}
	)


def actor_list(request):
	page = 1 if not request.GET.get("page") else int(request.GET.get("page"))
	total_list = list(ActorModel.objects.all())
	p = Paginator(total_list, 24)
	item_list = p.page(page).object_list
	return render(
		request,
		"actor_list.html",
		{"actors": item_list, "paginator": paginator_list(page, math.ceil(len(total_list) / 24))}
	)


def actor(request, actor_id):
	movie_list = MovieModel.objects.filter(actors__actorID=actor_id).distinct()
	h = {}
	for movie in movie_list:
		for actor in movie.actors.all():
			if actor.actorID != actor_id:
				if actor.actorID in h:
					h[actor.actorID] += 1
				else:
					h[actor.actorID] = 1
	cooperate_actors_h = sorted([(key, value) for key, value in h.items()], key=lambda x: -x[1])[0: 10]
	cooperate_actors = []
	for actor_h in cooperate_actors_h:
		cooperate_actors.append({
			"name": ActorModel.objects.filter(actorID=actor_h[0])[0].name,
			"actorID": actor_h[0],
			"times": actor_h[1]
		})
	return render(
		request,
		"actor.html",
		{
			"actor": ActorModel.objects.filter(actorID=actor_id)[0],
			"movie_list": movie_list,
			"cooperate_actors": cooperate_actors
		}
	)


def search_result(request):
	start_time = time.time()
	type = request.GET.get("type")
	keyword = request.GET.get("keyword")
	page = 1 if not request.GET.get("page") else int(request.GET.get("page"))
	if type == "影视":
		total_list = MovieModel.objects.filter(Q(name__contains=keyword) | Q(actors__name__contains=keyword)).distinct()
		p = Paginator(total_list, 12)
		item_list = p.page(page).object_list
		paginator = paginator_list(page, math.ceil(len(total_list) / 12))
	elif type == "演员":
		total_list = ActorModel.objects.filter(Q(name__contains=keyword) | Q(moviemodel__name__contains=keyword)).distinct()
		p = Paginator(total_list, 24)
		item_list = p.page(page).object_list
		paginator = paginator_list(page, math.ceil(len(total_list) / 24))
	else:
		total_list = CommentModel.objects.filter(content__contains=keyword)
		p = Paginator(total_list, 15)
		item_list = p.page(page).object_list
		paginator = paginator_list(page, math.ceil(len(total_list) / 15))
	return render(
		request,
		"search_result.html",
		{
			"keyword": keyword,
			"type": type,
			"result": item_list,
			"runtime": round((time.time() - start_time) * 1000),
			"paginator": paginator,
			"total_results": len(total_list)
		}
	)
