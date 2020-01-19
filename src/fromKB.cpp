#include <fromKB.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include <ClientData.h>

using namespace std;


fromKB::fromKB(ConnectionHandler &ch, int isConnected, ClientData &clientData, mutex &mutex):
        ch(ch),
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
                int subid = clientData->getSubID();
                string action = to_string(subid) +" " + "join" + " " + words[1];
                string frame = "SUBSCRIBE" + newLine + "destination:" + words[1] + newLine + "id: " + to_string(subid) + newLine + + "receipt:" + to_string(receiptid) + newLine+newLine+newLine + '\0';
                if(ch.sendLine(frame)){
                    clientData->addReceipt(receiptid, action);
                }
            }
            if (words[0] == "exit") {
                string genre = words[1];
                int subID = clientData->getGenreSubID(genre);
                //create SUBSCRIBE frame
                string frame = "UNSUBSCRIBE" + newLine + "id:" + to_string(subID) + newLine+newLine+newLine + '\0';
                //if succeed to send the frame, add an action for getting SUBSCRIBED frame from the server
                if(ch.sendLine(frame)){
                    clientData->addReceipt(clientData->getReceiptID(), "Exited " + genre);
                }

            }
            if (words[0] == "add") {
                string genre = words[1];
                string book = words[2];
                string name = clientData->getName();
                //create SEND frame
                string frame = "SEND" + newLine + name + " has added the book" + book + newLine+newLine+newLine + '\0';
                //if succeed to send the frame, add the book to user's inventory
                if(ch.sendLine(frame)){
                    clientData->addBook(genre,book,name);
                }
            }
            if (words[0] == "borrow") {
                string genre = words[1];
                string book = words[2];
                string name = clientData->getName();
                //create SEND frame
                string frame = "SEND" + newLine + "destination:" + genre + newLine + name + " wish to borrow " + book + newLine+newLine+newLine + '\0';
                //if succeed to send the frame, add the book to user's inventory
                if(ch.sendLine(frame)) {
                    clientData->addToWL(genre,book);
                }
            }
            if (words[0] == "return") {
                string genre = words[1];
                string book = words[2];
                string name = clientData->getName();
                string owner = clientData->getInventory().at(genre).at({book, true});
                //create SEND frame
                string frame = "SEND" + newLine + "destination:" + genre + newLine + "Returning " + book + " to" + "owner" + newLine+newLine+newLine + '\0';
                //if succeed to send the frame, add the book to user's inventory
                if(ch.sendLine(frame)) {
                    clientData->removeBookInventory(genre, book);
                }
            }
            if (words[0] == "status") {
                string genre = words[1];
                string name = clientData->getName();
                //create SEND frame
                string frame = "SEND" + newLine + "destination:" + genre + newLine + "book status" + newLine+newLine+newLine + '\0';
                ch.sendLine(frame);
            }
            if (words[0] == "logout") {
                int receiptid = clientData->getReceiptID();
                string frame = "DISCONNECT" + newLine + "receipt:" + to_string(receiptid )+  newLine+newLine+newLine + '\0';
                if (ch.sendLine(frame)){
                    //add receiptID and action to act when getting a receipt with this id.
                    clientData->addReceipt(receiptid, "disconnect");
                    //update client's connection status for stop getting KB commands
                    clientData->setConnected(false);
                }
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


//    void run() {
//            for (int i = 0; i < 100; i++) {
//                std::lock_guard<std::mutex>
//                lock(mutex); // constructor locks the mutex while destructor (out of scope) unlocks it
//                std::cout << i << ") Task " << /*_id << */" is working" << std::endl;
//            }
//    }






