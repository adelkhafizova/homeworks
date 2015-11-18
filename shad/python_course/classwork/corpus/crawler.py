import re
from requests import get, post
import urllib
from bs4 import BeautifulSoup

wiki_template = 'https://mo.wikipedia.org{}'

visited_pages = {}

def process(query, level):
    ++level
    url = wiki_template.format(query)
    req = get(url)
    
    soup = BeautifulSoup(req.content.decode(req.encoding), 'lxml')
    for link in soup.findAll('a'):
        if str(link).find('/wiki/') == 9:
            begin, link = str(link).split('"', 1)
            link, rest = link.split('"', 1)
            if visited_pages.get(link, None) is None:
                visited_pages[link]  = level
                process(link, level)
            #print link
            #print u' '.join(map(unicode, link.contents))

    #url = query_template.format(urllib.urlencode({'q': query}))
    #req = get(url)
    #print req.status_code, req.encoding
    #soup = BeautifulSoup(req.content.decode(req.encoding), 'lxml')
    #for li in soup.findAll('li', attrs={'class' : 'g'}):
    #    link = li.find('a')
    #    if link:
    #        print u' '.join(map(unicode, link.contents))

if __name__ == '__main__':
    query = ''
    level = 0
    process(query, level)
    print(visited_pages)
