
#include <connectionHandler.h>
#include <fromKB.h>
#include <ClientData.h>

using namespace std;

int main() {
    bool login = false;
    const short bufsize = 1024;
    char buf[bufsize];
    cin.getline(buf, bufsize);
    string line(buf);
    vector<string> words;
    while (!login) {
        if (line.substr(0, 5).compare("login")) {
            bool wantedLogout = false;
            size_t pos = 0;
            std::string token;
            string delimiter = " ";
            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                words.push_back(token);
                line.erase(0, pos + delimiter.length());
                words.push_back(line);
                login = true;
            }
        }
    }
    //login user
    string newLine = "/n";
    int endPos = words[1].find(":");
    string host = words[1].substr(0, endPos);
    string port = words[1].substr((endPos + 1));
    ClientData clientData(words[2], words[3]);
    ConnectionHandler connectionHandler(host, short(stoi(port)));
    connectionHandler.connect();
    mutex mutex;
    fromKB fromKb(connectionHandler, -1, clientData, mutex);
    string frame = "accept-version:1.2" + newLine + "host: " + host + newLine + "login: " + words[2] + newLine +

//
//        int *isConnected = new int(0);
//
//
//
//        if (!connectionHandler.connect()) { //handeling fail in connection
//            std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
//            return 1;
//        }
//
//        fromKB readTask(&connectionHandler, isConnected);
//        std::thread th1(readTask);
//
//        while (1) {
//            Packet *p = connectionHandler.decodeNextMessage();
//            protocol.process(p);
//            delete p;
//            if (connectionHandler.IsDisconnectApproved()) {
//                break;
//            }
//        }
//
//        th1.join();
//        delete islogged;
//        return 0;




}