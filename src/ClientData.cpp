
#include "ClientData.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

ClientData::ClientData(string userName, string password):userName(userName), password(password){
    topicsID = map<string, int>();
    inventory = map <string, map<pair<string, bool>, string>>();
    wishList = map<string,vector<string>>();
    receipts = map <int, string>();
    connected = false;
    subID = 0;
    receiptID = 0;
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
    if(inventory.count(genre));
    inventory.at(genre).emplace(make_pair(book,true), owner);
}

string ClientData::getName() {
    return userName;
}

void ClientData::setName(string name) {
    userName = name;
}

void ClientData::addToWL(string genre, string book) {
    if (wishList.count(genre) == 0)
        wishList.emplace(genre, vector<string>());
    wishList.at(genre).push_back(book);
}

map<string, map<pair<string, bool>, string>> ClientData::getInventory() {
    return inventory;
}

void ClientData::removeBookInventory(string genre, string book) {
    inventory.at(genre).erase(make_pair(book, true));
    inventory.at(genre).erase(make_pair(book, false));
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

bool ClientData::checkBookInventory(string genre, string book) {
    return (inventory.at(genre).count(make_pair(book,true))==1);
}

void ClientData::lendBook(string genre, string book) {
    string owner = inventory.at(genre).at(make_pair(book, true));
   inventory.at(genre).erase(make_pair(book, true));
    inventory.at(genre).emplace(make_pair(book, false), owner);
}

bool ClientData::checkBookWL(string genre, string book) {
    return(find(wishList.at(genre).begin(), wishList.at(genre).end(), book) == wishList.at(genre).end());
}

void ClientData::removeBookWL(string genre, string book) {
    vector<string> genreBooks = wishList.at(genre);
   genreBooks.erase(remove(genreBooks.begin(),genreBooks.end(), book), genreBooks.end());
}

string ClientData::getOwner(string genre, string book) {
    return (inventory.at(genre).at(make_pair(book,false)));
}

void ClientData::returnBooktoMe(string genre, string book) {
    inventory.at(genre).erase(make_pair(book, false));
    inventory.at(genre).emplace(make_pair(book, true), userName);
}

string ClientData::genreStatus(string genre) {
    string books = userName+ ":";
    vector<pair<string, bool>> v;
    map<pair<string, bool>, string> genreMap = inventory.at(genre);
    for(map<pair<string, bool>, string>::iterator it = genreMap.begin(); it != genreMap.end(); ++it) {
        v.push_back(it->first);
        for (pair<string, bool> book : v ){
            if (book.second)
                books = books+book.first;
        }
    }
    return books;
}





ClientData::~ClientData() = default;


