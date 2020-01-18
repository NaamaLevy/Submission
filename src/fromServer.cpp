#include <fromServer.h>
#include <vector>
#include <connectionHandler.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <ClientData.h>
using namespace std;

fromServer::fromServer(ConnectionHandler* ch, int isConnected, ClientData &clientData, mutex &mutex):
        connectionHandler(ch),
        isConnected(isConnected),
        clientData(&clientData), _mutex(mutex){
}

    void fromServer::operator()() {
            while (1) {// we wants to read as long as there is a connection to the server
                const short bufsize = 1024;
                char buf[bufsize];
                std::cin.getline(buf, bufsize);
                std::string line(buf);
                bool wantedLogout= false;
                std::vector<std::string> words = split(line, '\n');
                if (words[0] == "CONNECTED") {
                    clientData->setConnected(true);
                }
                if (words[0] == "ERROR") {


                }
                if (words[0] == "RECEIPT") {
                    int receiptid = stoi(words[1]); //add the same algorithm as in the server side.
                    string action = clientData->getAction(receiptid);
                    vector<string> act;
                    split(act, action, " ");
                    if (act[1].compare("join")){
                        clientData->setSub(stoi(act[0]), act[2]);
                    }

                }
                if (words[0] == "MESSAGE") {

                }


                if (disconnected){
                    break;
                }
            }
    }
    void run() {
        for (int i = 0; i < 100; i++) {
            std::lock_guard<std::mutex>
            lock(mutex); // constructor locks the mutex while destructor (out of scope) unlocks it
            std::cout << i << ") Task " << _id << " is working" << std::endl;
        }
    }

    void fromServer::split(std::vector<std::string> &vector, std::string s, std::string delimiter) {
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        vector.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    vector.push_back(s);
    }