#include <fromServer.h>
#include <vector>
#include <connectionHandler.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <ClientData.h>

using namespace std;

fromServer::fromServer(ConnectionHandler &ch, int isConnected, ClientData &clientData, mutex &mutex):
        connectionHandler(ch),
        isConnected(isConnected),
        clientData(&clientData), _mutex(mutex){
}

    void fromServer::operator()() {
            while (isConnected) {// we wants to read as long as there is a connection to the server
                const short bufsize = 1024;
                char buf[bufsize];
                std::cin.getline(buf, bufsize);
                std::string line(buf);
                bool wantedLogout= false;
                std::vector<std::string> words;
                split(words, line, " ");
                std::string newLine = "/n";
                while (isConnected & !clientData->isConnected()){
                    if (words[0] == "CONNECTED") {
                        clientData->setConnected(true);
                     }
                    if (words[0] == "ERROR") {
                        //extract a message to print on the client's screen
                        string message = words[4];
                        message = message.substr(9,message.size()-1);
                        //print message
                        cout << message<< endl;
                    }
                }
                while(clientData->isConnected()){
                    if (words[0] == "ERROR") {
                    }
                    if (words[0] == "RECEIPT") {
                        int receiptid = stoi(words[1]); //add the same split algorithm as in the server side.
                        string action = clientData->getAction(receiptid);
                        vector<string> act;
                        split(act, action, " ");
                        if (act[1].compare("join")){
                            string genre = act[2];
                            //add genre to ClientData - topicsID and inventory
                            clientData->setSub(stoi(act[0]), genre);
                            //print the required message on the client screen
                            cout << "Joined club " + genre << endl;
                        } else if (act[0].compare("Exited")){
                            string genre = act[1];
                            //delete genre from all the DBs
                            clientData->exitClub(genre);
                            //print the required message on the client screen
                            cout << "Exited club " + genre << endl;
                        } else if (act[0].compare("disconnect")){
                            //delete client's data
                            delete(clientData);
                            //change connected to exit the loop and stop getting Server commands
                            isConnected = false;
                        }
                    }
                    if (words[0] == "MESSAGE") {

                    }
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