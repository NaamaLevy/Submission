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
        ch(ch),
        isConnected(isConnected),
        clientData(&clientData), _mutex(mutex){
}

    void fromServer::operator()() {
            while (isConnected) {// we wants to read as long as there is a connection to the server
                const short bufsize = 1024;
                char buf[bufsize];
                cin.getline(buf, bufsize);
                string line(buf);
                std::vector<std::string> lines;
                split(lines, line, " ");
                //get command
                string command = lines[0];
                // get headers
                bool head = true;
                int i = 1;
                map<string, string> headers;
                string body;
                while (i<lines.size()-1){
                    while(head){

                        string header;
                        header = lines[i];
                        if (header.compare(""))
                            head = false;
                        int index = header.find(":");
                        string key = header.substr(0, index);
                        string value = header.substr(index + 1, header.length());
                        headers.insert(key, value);
                        i++;
                    }
                    //get body
                    if (!lines[i+1].compare(""))
                        body = lines[i+1];
                }
                std::string newLine = "/n";
                while (isConnected & !clientData->isConnected()){
                    if (command == "CONNECTED") {
                        clientData->setConnected(true);
                     }
                    if (command == "ERROR") {
                        //extract a message to print on the client's screen
                        string message = headers.at("message");
                        //print message
                        cout << message<< endl;
                    }
                }
                while(clientData->isConnected()){
//                    if (command == "ERROR") {
//                    }
                    if (command == "RECEIPT") {
                        int receiptid = stoi(headers.at("receipt-id")); //add the same split algorithm as in the server side.
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
                    if (command == "MESSAGE") {
                        vector<string> message;
                        split(message, body, " ");
                        //borrow wish message
                        if (message[3].compare("borrow")){
                            string genre = headers.at("destination");
                            if (!clientData->getName().compare(message[0])){
                                if(clientData->checkBook(genre, message[4])) {
                                    string frame = "SEND" + newLine + "destination:" + genre + newLine +
                                                   clientData->getName() + " has " + message[4] + newLine + newLine +
                                                   newLine + '\0';
                                    (ch.sendLine(frame));
                                }
                            }
                        }
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