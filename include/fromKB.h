
#ifndef BOOST_ECHO_CLIENT_FROMKB_H
#define BOOST_ECHO_CLIENT_FROMKB_H

#endif //BOOST_ECHO_CLIENT_FROMKB_H
#include <iostream>
#include <mutex>
#include <thread>
#include "connectionHandler.h"
#include "ClientData.h"

class fromKB {
private:
    int _id;
    mutex &_mutex;
    ConnectionHandler* connectionHandler;
    int isConnected;
    ClientData clientData;

public:
    fromKB(ConnectionHandler *ch, int isConnected, ClientData clientData, mutex &mutex);

    void run();
    void operator()();

    fromKB &operator=(const fromKB &other);
    std::vector<std::string> split(std::string s, std::string delimiter);


    void split(std::vector<std::string> &vector, std::string s, std::string delimiter);
};