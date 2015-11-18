from bottle import route, run, static_file, request
import urllib
import os
                            
author_template = '<h4>{}</h4>'
book_template = '<a href={}> {} </a><br />'
url_template = '/lib/book?{}'

@route('/hello')
def hello():
    return 'Hello, world!'

@route('/lib/index')
def get_index():
    result = ''
    for author in os.listdir('.'):
        if os.path.isdir(author):
            result += author_template.format(author)
            for book in os.listdir(author):
                args = {
                        'author':author, 'book': book
                }
                url = url_template.format(urllib.urlencode(args))
                result += book_template.format(url, book)
    return result

@route('/lib/book')
def get_book():
    book = '{}/{}'.format(request.query.author, request.query.book)
    return static_file(book, root = '.')

run(host='localhost', port=8080, debug=True)
