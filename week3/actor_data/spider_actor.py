from urllib.request import Request, urlopen, urlretrieve
import re
from itertools import islice
import os
import json
import time
import random
import html

Header = "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/76.0.3809.100 Safari/537.36"
output = open("actors.json", "a")

def extract(url):
	req = Request(url)
	req.add_header("User-Agent", Header)
	sourceCode = urlopen(req).read().decode("utf-8")
	ID = re.search(r'[\s\S]+?([\d]+)', url).group(1)
	name = html.unescape(re.search(r'<a class="nbg" title="([\s\S]+?)"', sourceCode).group(1))
	description = re.search(r'<div id="intro" class="mod">[\s\S]+?<div class="bd">[\s]+([\s\S]*?)</div>', sourceCode).group(1)
	if (re.search(r'<span class="all hidden">', sourceCode)):
		description = re.search(r'<span class="all hidden">[\s]+([\s\S]+?)</span>', sourceCode).group(1)
	description = html.unescape(re.sub(r'[\s]*<br/>[\s]*', "\n", description))
	try:
		gender = re.search(r'<span>性别</span>:\s+(\S+)', sourceCode).group(1)
	except AttributeError:
		gender = "N/A"
	try:
		os.system("wget " + re.search(r'title="点击看大图"\s+src="(\S+?)">', sourceCode).group(1) + " -O %s.jpg" % ID)
	except AttributeError:
		pass
	try:
		hometown = html.unescape(re.search(r'<span>出生地</span>:\s+(\S+)', sourceCode).group(1))
	except AttributeError:
		hometown = "N/A"
	print(json.dumps({"name": name, "ID": ID, "description": description, "gender": gender, "hometown": hometown}, ensure_ascii = False), file = output)
	print(name)

start = int(input())
h = set()
cnt = 0
for line in open("movies.json"):
	info = json.loads(line)
	for actor in info["actors"]:
		if (not actor["id"] in h):
			h.add(actor["id"])
			cnt += 1
			if (cnt >= start):
				extract("https://movie.douban.com/celebrity/%s/" % actor["id"])
				time.sleep(random.randint(1, 2))
				print(cnt)
