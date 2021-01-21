import erpc
import prog
from prog import pippo

if __name__ == '__main__':
    transport = erpc.transport.TCPTransport('localhost', 12345, False)

    clientManager = erpc.client.ClientManager(transport, erpc.basic_codec.BasicCodec)

    client = pippo.client.plutoClient(clientManager)

    val = client.leggi()
    print("leggo {}".format(val))
    val+=1
    print(client.scrivi(val))
    val = client.leggi()
    print("leggo {}".format(val))
    transport.close()
