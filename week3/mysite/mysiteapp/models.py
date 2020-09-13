from django.db import models


class ActorModel(models.Model):
	name = models.CharField(max_length=100)
	actorID = models.IntegerField(default=0)
	description = models.CharField(max_length=1000)
	gender = models.CharField(max_length=10)
	hometown = models.CharField(max_length=100)


class MovieModel(models.Model):
	name = models.CharField(max_length=100)
	movieID = models.IntegerField(default=0)
	year = models.IntegerField(default=0)
	description = models.CharField(max_length=1000)
	actors = models.ManyToManyField(ActorModel)
	duration = models.IntegerField(default=0)


class CommentModel(models.Model):
	content = models.CharField(max_length=500)
	movie = models.ForeignKey(MovieModel, on_delete=models.CASCADE)
