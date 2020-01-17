#include <fromKB.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include <ClientData.h>

using namespace std;


fromKB::fromKB(ConnectionHandler* ch, int isConnected, ClientData clientData, mutex &mutex):
        connectionHandler(ch),
        isConnected(isConnected),
        clientData(clientData), _mutex(mutex){
}




    void fromKB::operator()() {
        while (1) {// we wants to read as long as there is a connection to the server
            const short bufsize = 1024;
            char buf[bufsize];
            std::cin.getline(buf, bufsize);
            std::string line(buf);
            bool wantedLogout= false;
            std::vector<std::string> words;
            split(words, line, " ");
            std::string newLine = "/n";
            if (words[0] == "login") {
                int pos = words[1].find(":");
                std::string host = words[1].substr(0,pos);
                std::string frame = "accept-version:1.2" + newLine + "host: " + host + newLine + "login: " + words[2] + newLine + "passcode: " + words[3] + newLine+newLine+newLine + '\u0000';
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


    void fromKB::split(std::vector<std::string> &vector, std::string s, std::string delimiter) {
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            vector.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        vector.push_back(s);
    }






