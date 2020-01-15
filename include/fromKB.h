
#ifndef BOOST_ECHO_CLIENT_FROMKB_H
#define BOOST_ECHO_CLIENT_FROMKB_H

#endif //BOOST_ECHO_CLIENT_FROMKB_H
#include <iostream>
#include <mutex>
#include <thread>
class fromKB {
private:
    int _id;
    std::mutex & _mutex;
public:
    fromKB (int id, std::mutex& mutex) : _id(id), _mutex(mutex) {}

    void run(){
        for (int i= 0; i < 100; i++){
            std::lock_guard<std::mutex> lock(_mutex); // constructor locks the mutex while destructor (out of scope) unlocks it
            std::cout << i << ") Task " << _id << " is working" << std::endl;
        }
    }
};