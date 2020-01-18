//
// Created by levynaa@wincs.cs.bgu.ac.il on 16/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENTDATA_H
#define BOOST_ECHO_CLIENT_CLIENTDATA_H

#include <map>
#include <list>
#include <string>
#include <vector>
#include <atomic>

using namespace std;


class ClientData {
public:
    ClientData(string userName, string password);
    virtual ~ClientData();

private:
    map <string, int> topicsID; //map<genre, id>
    map <string, map<pair<string, bool>, string>> inventory; //map<genre, map<<book, isAvailable>, owner>
    vector<string> wishList; //map<book i want>
    map <int, string> receipts; //map<receipt id, action> //map an action to act when getting a receipt with this id.
    atomic_int subID; //produces unique id for every sub' genre
    bool connected;
    string userName;
    string password;
    atomic_int receiptID;
public:
   int getSubID();
   void addReceipt(int receiptID, string action);
   int getReceiptID();
   void setConnected(bool status);
   string getAction(int receiptid);
   void setSub(int subid, string genre);
   bool isConnected();
   void addBook(string genre, string book, string owner);
   string getName();
   void addToWL(string book);
};


#endif //BOOST_ECHO_CLIENT_CLIENTDATA_H
