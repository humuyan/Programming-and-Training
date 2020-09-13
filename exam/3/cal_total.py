from html.parser import HTMLParser
import re

in_td = False
in_abbr = False
num_added = False
ans = []
date = []

class HTMLTableParser(HTMLParser):
	def handle_starttag(self, tag, attrs):
		global in_td, in_abbr, num_added
		if tag == "td":
			in_td = True
			num_added = False
		if tag == "abbr":
			in_abbr = True

	def handle_endtag(self, tag):
		global in_td, in_abbr
		if tag == "td":
			in_td = False
			if not num_added:
				ans.append(0)
		if tag == "abbr":
			in_abbr = False

	def handle_data(self, data):
		global in_td, in_abbr, ans, date, num_added
		if in_td:
			ans.append(int(data))
			num_added = True
		if in_abbr and re.search(r'\d', data):
			date.append(data)


state_name = []
for line in open("states.txt"):
	state_name.append(line[0: 2])
parser = HTMLTableParser()
parser.feed(''.join(open("COVID19_US.html").readlines()))
tot_cases = 0
cur_index = 0
output = open("trend.txt", "w")
state_cases_count = [0] * len(state_name)
for day in date:
	cur_cases = 0
	for i in range(len(state_name)):
		cur_cases += ans[cur_index]
		state_cases_count[i] += ans[cur_index]
		cur_index += 1
	tot_cases += cur_cases
	print(day, cur_cases, tot_cases, sep=',', file=output)
output = open("distrib.txt", "w")
for i in range(len(state_name)):
	print(state_name[i], state_cases_count[i], sep=',', file=output)
