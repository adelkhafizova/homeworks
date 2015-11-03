from tornado.gen import coroutine, Future, sleep
import tornado.tcpclient
from tornado.log import app_log as log
from tornado.iostream import StreamClosedError
from tornado.ioloop import IOLoop 
import construct


class Structs(object):

    HEADER = construct.Struct("Header",                                                                                                        
            construct.Magic(25),
            construct.UBInt32("serial"),
            construct.UBInt32("size"),
            #construct.Field("content", lambda ctx: ctx.size),
        )

    PACKET = construct.Struct('Packet',
            construct.Embed(HEADER),
            construct.Field('content', lambda ctx: ctx.size),
        )

    ACK = construct.Struct('Ack',
            construct.Embed(HEADER),
            construct.UBInt32('content'),
        )

class test_client(tcpclient.TCPClient):
    def __init__(self, host, port):                                                                                                            
        super(test_client, self).__init__()
        self.sequence = 0
        self.host = host
        self.port = port
        self.io_loop = IOLoop.current()
        self.fails = {}

    @coroutine
    def try_connect(self):
        yield self.add_old_points_to_work()
    
        try:
            log.debug('Starting connection to %s:%d', self.host, self.port)
            self.stream = yield self.connect(self.host, self.port)
        except Exception as e:
            log.error('Exception in try_connect: %s', e)
            self.io_loop.call_later(5, self.try_connect)                                                                                       
        else:
            log.info('Connection established: %s:%d', self.host, self.port)
        
            self.io_loop.add_callback(self.listener)

    @coroutine
    def listener(self):
        log.debug("Starting to listening")
        while not self.stream.closed():
            try:
                pass
#                hdr = yield self.thread_pool.submit(
#                        HEADER.parse,
#                        (yield self.stream.read_bytes(HEADER.sizeof()))
#                )
#
#                payload = yield self.thread_pool.submit(
#                       msgpack.loads,
#                       (yield self.stream.read_bytes(hdr.size))
#                    )

            except StreamClosedError as e:
                log.error(e)
                break

    @coroutine      
    def on_disconnect(self):
        while not self.stream.closed():
            yield sleep(1)

        self.try_connect()

test = test_client(
        host='0.0.0.0',
        port=10001)
test.thread_pool = futures.ThreadPoolExecutor(4)
io_loop = IOLoop.current()

io_loop.add_callback(try_connect) 
    

