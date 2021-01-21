import erpc
import prog
from prog import pippo


class Handler(pippo.interface.Ipluto):
    def __init__(self):
        self.val = 0

    def scrivi(self, val):
        self.val = val

    def leggi(self):
        return self.val


if __name__ == '__main__':
    transport = erpc.transport.TCPTransport('localhost', 12345, True)

    handler = Handler()

    service = pippo.server.plutoService(handler)

    server = erpc.simple_server.SimpleServer(transport, erpc.basic_codec.BasicCodec)
    server.add_service(service)
    server.run()
