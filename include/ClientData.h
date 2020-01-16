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
    map <map<string, bool>, string> inventory; //map<map<book, isAvailable>, owner>
    vector<string> wishList; //map<book i want>
    map <int, string> receipts; //map<receipt id, action> //map an action to act when getting a receipt with this id.
    atomic<int> subID; //produces unique id for every sub' genre
    bool loogedIn;
    string userName;
    string password;

public:
   int getSubID();

};


#endif //BOOST_ECHO_CLIENT_CLIENTDATA_H
