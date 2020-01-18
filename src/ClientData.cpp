
#include "ClientData.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

ClientData::ClientData(string userName, string password):userName(userName), password(password){
    topicsID = map<string, int>();
    inventory = map<map<string, bool>, string>();
    wishList = vector<string>();
    receipts = map <int, string>();
    connected = false;
}

//map <string, int> topicsID; //map<genre, id>
//map <map<string, bool>, string> inventory; //map<map<book, isAvailable>, owner>
//vector<string> wishList; //map<book i want>
//map <int, string> receipts; //map<receipt id, action> //map an action to act when getting a receipt with this id.
//atomic<int> subID; //produces unique id for every sub' genre
//bool loogedIn;
//string userName;
//string password;


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
}
