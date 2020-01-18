
#include "ClientData.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

ClientData::ClientData(string userName, string password):userName(userName), password(password){
    topicsID = map<string, int>();
    inventory = map <string, map<pair<string, bool>, string>>();
    wishList = map<string,vector<string>>();
    receipts = map <int, string>();
    connected = false;
}
//map <string, int> topicsID; //map<genre, id>
//map <string, map<pair<string, bool>, string>> inventory; //map<genre, map<<book, isAvailable>, owner>
//map<string,vector<string>> wishList; //map<genre, vector<book i want>>
//map <int, string> receipts; //map<receipt id, action> //map an action to act when getting a receipt with this id.
//atomic_int subID; //produces unique id for every sub' genre
//bool connected;
//string userName;
//string password;
//atomic_int receiptID;

int ClientData::getSubID() {
    return subID++;
}
void ClientData::addReceipt(int receiptID, string action){
    receipts.insert({receiptID, action});

}
int ClientData::getReceiptID(){
    return receiptID++;
}
void ClientData::setConnected(bool status) {
    connected = status;
}
string ClientData::getAction(int receiptid){
    return receipts.at(receiptid);
}
void ClientData:: setSub(int subid, string genre){
    topicsID.insert({genre, subid});
    inventory.emplace(genre, map<pair<string, bool>,string>());
}

bool ClientData::isConnected() {
    return connected;
}

void ClientData::addBook(string genre, string book, string owner) {
    inventory.at(genre).emplace(make_pair(book,true), owner);
}

string ClientData::getName() {
    return userName;
}

void ClientData::addToWL(string genre, string book) {
    if (wishList.count(genre) == 0)
        wishList.emplace(genre, vector<string>());
    wishList.at(genre).push_back(book);
}

map<string, map<pair<string, bool>, string>> ClientData::getInventory() {
    return inventory;
}

void ClientData::removeBook(string genre, string book) {
    inventory.at(genre).erase(make_pair(book, true));

}

int ClientData::getGenreSubID(string genre) {
    return topicsID.at(genre);
}

void ClientData::exitClub(string genre) {
    //remove genre and its books from the WL
    wishList.at(genre).clear();
    wishList.erase(genre);
    //remove genre and its books from the inventory
    inventory.at(genre).clear();
    inventory.erase(genre);
    //remove genre and its subID from topicsID
    topicsID.erase(genre);
}

bool ClientData::checkBook(string genre, string book) {
    return (inventory.at(genre).count(make_pair(book,true)));
}

void ClientData::lendBook(string genre, string book) {
    inventory.at(genre).
}

ClientData::~ClientData() = default;


