
#ifndef BOOST_ECHO_CLIENT_FROMSERVER_H
#define BOOST_ECHO_CLIENT_FROMSERVER_H

#endif //BOOST_ECHO_CLIENT_FROMSERVER_H

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>


class fromServer {
private:
    int _id;
    std::mutex & _mutex;
    bool disconnected;


public:
    fromServer (int id, std::mutex& mutex) : _id(id), _mutex(mutex) {}

    void run(){
        for (int i= 0; i < 100; i++){
            std::lock_guard<std::mutex> lock(_mutex); // constructor locks the mutex while destructor (out of scope) unlocks it
            std::cout << i << ") Task " << _id << " is working" << std::endl;
        }
    }

    void operator()();

    std::vector<std::string> split(std::string s, char delimiter);

    std::vector<std::string> split(std::string s, std::string delimiter);
};