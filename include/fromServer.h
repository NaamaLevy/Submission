
#ifndef BOOST_ECHO_CLIENT_FROMSERVER_H
#define BOOST_ECHO_CLIENT_FROMSERVER_H

#endif //BOOST_ECHO_CLIENT_FROMSERVER_H

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include "ClientData.h"
#include "connectionHandler.h"

using namespace std;

class fromServer {
private:
    int _id;
    mutex _mutex;
    bool disconnected;
    ClientData* clientData;
    ConnectionHandler* ch;
    int isConnected;

public:
    fromServer(ConnectionHandler *ch, int isConnected, ClientData &clientData, mutex &mutex);

    void run();

    void operator()();


    void split(std::vector<std::string> &vector, std::string s, std::string delimiter);
};