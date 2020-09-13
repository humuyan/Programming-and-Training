from urllib.request import Request, urlopen
import re
from itertools import islice
import os
import json
import time
import random

Header = "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/76.0.3809.100 Safari/537.36"
output = open("movies.json", "a")

def extract(url):
	req = Request(url)
	req.add_header("User-Agent", Header)
	html = urlopen(req).read().decode("utf-8")
	ID = re.search(r'"url": "/subject/([\d]+)', html).group(1)
	title = re.search(r'<input type="hidden" name="title" value="([\S\s]+?) \(([\d]+?)\)">', html)
	name = title.group(1).replace("&#39;", "'")
	year = int(title.group(2))
	description = re.search(r'<span property="v:summary"[\s\S]*?>[\s]+([\S\s]+?)[\s]+</span>', html).group(1)
	if (re.search(r'<span class="all hidden">', html)):
		description = re.search(r'<span class="all hidden">[\s]+([\S\s]+?)[\s]+</span>', html).group(1)
	description = re.sub(r'[\s]+<br />[\s]+', "\n", description)
	actors = []
	for actor in islice(re.finditer(r'<a href="/celebrity/([\d]+)/" rel="v:starring">([\s\S]+?)</a>', html), 10):
		actors.append({"name": actor.group(2), "id": actor.group(1)})
	duration = 0 if not re.search(r'<span property="v:runtime"', html) else int(re.search(r'<span property="v:runtime" content="([\d]+)">', html).group(1))
	os.system("wget " + re.search(r'<img src="(http[\S\s]+?)" title="点击看更多海报"', html).group(1) + " -O " + ID + ".jpg")
	req = Request(url + "comments?status=P")
	req.add_header("User-Agent", Header)
	html = urlopen(req).read().decode("utf-8")
	comments = []
	for comment in islice(re.finditer(r'<span class="short">([\s\S]+?)</span>', html), 5):
		comments.append(comment.group(1).replace("&#39;", "'"))
	print(json.dumps({"name": name, "ID": ID, "year": year, "description": description, "actors": actors, "duration": duration, "comments": comments}, ensure_ascii = False), file = output)
	print(name)

start = int(input())
index = open("lengmen.txt").readline()
cnt = 0
for url in re.finditer(r'"url":"(http[\s\S]+?)"', index):
	if (cnt >= start):
		extract(url.group(1).replace("\\", ""))
		time.sleep(random.randint(2, 3))
		print(cnt)
	cnt += 1