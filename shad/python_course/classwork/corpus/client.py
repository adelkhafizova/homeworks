from requests import get, post
import urllib
from bs4 import BeautifulSoup

query_template = 'https://www.google.ru/search?{}'

def main(query):
    url = query_template.format(urllib.urlencode({'q': query}))
    req = get(url)
    print req.status_code, req.encoding
    soup = BeautifulSoup(req.content.decode(req.encoding), 'lxml')
    for li in soup.findAll('li', attrs={'class' : 'g'}):
        link = li.find('a')
        if link:
            print u' '.join(map(unicode, link.contents))

if __name__ == '__main__':
    query = 'banana'
    main(query)
