from mysiteapp.models import ActorModel, MovieModel, CommentModel
import json

for line in open("../actor_data/actors.json"):
	info = json.loads(line)
	m_actor = ActorModel(
		name=info["name"],
		actorID=info["ID"],
		description=info["description"],
		gender=info["gender"],
		hometown=info["hometown"]
	)
	m_actor.save()
for line in open("../movie_data/movies.json"):
	info = json.loads(line)
	m_movie = MovieModel(
		name=info["name"],
		movieID=info["ID"],
		year=info["year"],
		description=info["description"],
		duration=info["duration"]
	)
	m_movie.save()
	for actor in info["actors"]:
		m_movie.actors.add(ActorModel.objects.filter(actorID=actor["id"])[0])
	for comment in info["comments"]:
		m_comment = CommentModel(content=comment, movie=m_movie)
		m_comment.save()
