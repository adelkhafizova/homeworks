from bottle import route, run
                                          
@route('/hello')
def hello():
    return 'Hello, world!'

@route('/lib/index')
def get_index():
    for author in os.listdir():
        if os.path.isdir(author):
            result += author + '\n'
    return result

run(host='localhost', port=8080, debug=True)
