
#include <Client.h>
#include <connectionHandler.h>
#include <fromKB.h>

int main(int argc, char *argv[]) {
    int* isConnected=new int(0);
  /*  if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }*/
    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);

    if (!connectionHandler.connect()) { //handeling fail in connection
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    fromKB readTask(&connectionHandler,isConnected);
    std::thread th1(readTask);

    while (1) {
        Packet *p = connectionHandler.decodeNextMessage();
        protocol.process(p);
        delete p;
        if (connectionHandler.IsDisconnectApproved()) {
            break;
        }
    }

    th1.join();
    delete islogged;
    return 0;
}
