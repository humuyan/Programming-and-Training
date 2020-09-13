import re


def main():
    output = open("states.txt", "w");
    source_code = ''.join(open("COVID19_US.html").readlines())
    for item in re.finditer(r'<th><a href="(https://en.wikipedia.org/wiki/COVID-19_pandemic_in_([\S]+?))"[\s]+title="COVID-19 pandemic in [\S]+?"><abbr title="[\S]+?">([\S]+?)</abbr></a></th>', source_code):
        print(item[3], item[2], item[1], sep=',', file=output)


if __name__ == '__main__':
    main()
