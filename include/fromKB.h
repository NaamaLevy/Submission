
#ifndef BOOST_ECHO_CLIENT_FROMKB_H
#define BOOST_ECHO_CLIENT_FROMKB_H

#endif //BOOST_ECHO_CLIENT_FROMKB_H
#include <iostream>
#include <mutex>
#include <thread>
#include "connectionHandler.h"

class fromKB {
private:
//    int _id;
//    std::mutex &_mutex;
    ConnectionHandler* connectionHandler;
    int* isConnected;

public:
    fromKB(ConnectionHandler* connectionHundler, int* isConnected);
            //int id, std::mutex &mutex) : _id(id), _mutex(mutex){};

    void run();
    void operator()();

    fromKB &operator=(const fromKB &other);
    std::vector<std::string> split(std::string s, std::string delimiter);




}