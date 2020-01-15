#include <fromKB.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <fromServer.h>










//private:
//    int _id;
//    std::mutex & _mutex;


fromKB::fromKB(ConnectionHandler* ch, int* isConnected):
connectionHandler(ch),
isConnected(isConnected){}



void fromKB::run() { //TODO why does it here
    for (int i = 0; i < 100; i++) {
        std::lock_guard<std::mutex> lock(
                _mutex); // constructor locks the mutex while destructor (out of scope) unlocks it
        std::cout << i << ") Task " << _id << " is working" << std::endl;
    }
}


void fromKB::operator()() {
    while (1) {// we wants to read as long as there is a connection to the server
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        bool wantedLogout= false;
        std::vector<std::string> words = split(line, " ");

        if (words[0] == "login") {

        }
        if (words[0] == "join") {

        }
        if (words[0] == "exit") {

        }
        if (words[0] == "add") {

        }
        if (words[0] == "borrow") {

        }
        if (words[0] == "return") {

        }
        if (words[0] == "status") {

        }
        if (words[0] == "logout") {

        }
         if(disconnected){
             break;
         }
        }
    }


std::vector<std::string> fromServer::split(std::string s, std::string delimiter) {
    std::vector<std::string> list;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);

    return list;
}


