import json
import html

output = open("movies.json", "w")
h = set()
for line in open("movies_raw.json"):
	info = json.loads(line)
	if (not info["ID"] in h):
		h.add(info["ID"])
		info["name"] = html.unescape(info["name"])
		info["description"] = html.unescape(info["description"])
		for i in range(len(info["comments"])):
			info["comments"][i] = html.unescape(info["comments"][i])
		print(json.dumps(info, ensure_ascii = False), file = output)