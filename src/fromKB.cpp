#include <fromKB.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include <ClientData.h>

using namespace std;


fromKB::fromKB(ConnectionHandler &ch, int isConnected, ClientData &clientData, mutex &mutex):
        connectionHandler(ch),
        isConnected(isConnected),
        clientData(&clientData), _mutex(mutex){
}


    void fromKB::operator()() {
        while (clientData->isConnected()) {// we wants to read as long as there is a connection to the server
            const short bufsize = 1024;
            char buf[bufsize];
            std::cin.getline(buf, bufsize);
            std::string line(buf);
            bool wantedLogout= false;
            std::vector<std::string> words;
            split(words, line, " ");
            std::string newLine = "/n";
            if (words[0] == "join") {
                int receiptid = clientData->getReceiptID();
                int subid = clientData->getReceiptID();
                string action = to_string(subid) +" " + "join" + " " + words[1];
                string frame = "SUBSCRIBE" + newLine + "destination:" + words[1] + newLine + "id: " + to_string(subid) + newLine + + "receipt: " + to_string(receiptid) + newLine+newLine+newLine + '\0';
                if(ch->sendLine(frame)){
                    clientData->addReceipt(receiptid, action);
                }
            }
            if (words[0] == "exit") {

            }
            if (words[0] == "add") {
                string genre = words[1];
                string book = words[2];
                string name = clientData->getName();
                //create SEND frame
                string frame = "SEND" + newLine + name + " has added the book" + book + newLine+newLine+newLine + '\0';
                //if succeed to send the frame, add the book to user's inventory
                if(ch->sendLine(frame)){
                    clientData->addBook(genre,book,name);
                }
            }
            if (words[0] == "borrow") {
                string genre = words[1];
                string book = words[2];
                string name = clientData->getName();
                //create SEND frame
                string frame = "SEND" + newLine + "destination: " + genre + newLine + name + " wish to borrow " + book + newLine+newLine+newLine + '\0';
                //if succeed to send the frame, add the book to user's inventory
                if(ch->sendLine(frame)) {
                    clientData->addToWL(book);
                }
            }
            if (words[0] == "return") {
                string genre = words[1];
                string book = words[2];
                string name = clientData->getName();
                string owner = clientData->getInventory().at(genre).at({book, true});
                //create SEND frame
                string frame = "SEND" + newLine + "destination: " + genre + newLine + "Returning " + book + " to" + "owner" + newLine+newLine+newLine + '\0';
                //if succeed to send the frame, add the book to user's inventory
                if(ch->sendLine(frame)) {
                    clientData->removeBook(genre,book);
            }
            if (words[0] == "status") {

            }
            if (words[0] == "logout") {
                ///action
                clientData->setConnected(false);
            }
//            if(disconnected){
//                break;
//            }
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


    void run() {
            for (int i = 0; i < 100; i++) {
                std::lock_guard<std::mutex>
                lock(mutex); // constructor locks the mutex while destructor (out of scope) unlocks it
                std::cout << i << ") Task " << _id << " is working" << std::endl;
            }
    }






