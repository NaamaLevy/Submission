
#ifndef BOOST_ECHO_CLIENT_FROMKB_H
#define BOOST_ECHO_CLIENT_FROMKB_H

#endif //BOOST_ECHO_CLIENT_FROMKB_H
#include <iostream>
#include <mutex>
#include <thread>
#include "connectionHandler.h"
#include "ClientData.h"
#include <string>
using namespace std;

class fromKB {
private:
    int _id;
    ConnectionHandler& ch;
    bool isConnected;
    ClientData &clientData;

public:
    fromKB(ConnectionHandler &ch, bool isConnected, ClientData &clientData);

    void run();
    void operator()();
    void send();
    void split(std::vector<std::string> &vector, std::string s, std::string delimiter);

};