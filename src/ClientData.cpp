
#include "ClientData.h"


ClientData::ClientData(string userName, string password):userName(userName), password(password){}

//map <string, int> topicsID; //map<genre, id>
//map <map<string, bool>, string> inventory; //map<map<book, isAvailable>, owner>
//vector<string> wishList; //map<book i want>
//map <int, string> receipts; //map<receipt id, action> //map an action to act when getting a receipt with this id.
//atomic<int> subID; //produces unique id for every sub' genre
//bool loogedIn;
//string userName;
//string password;


    int ClientData::getSubID() {
        return loogedIn++;
    }
