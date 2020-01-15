#include <fromServer.h>
#include <vector>


void fromServer::operator()() {
        while (1) {// we wants to read as long as there is a connection to the server
            const short bufsize = 1024;
            char buf[bufsize];
            std::cin.getline(buf, bufsize);
            std::string line(buf);
            bool wantedLogout= false;
            std::vector<std::string> words = split(line, '\n');
            if (words[0] == "CONNECTED") {

            }
            if (words[0] == "ERROR") {


            }
            if (words[0] == "RECEIPT") {


            }
            if (words[0] == "MESSAGE") {

            }


            if (disconnected){
                break;
            }
        }
}

std::vector<std::string> fromServer::split(std::string s, std::string delimiter) {
    std::vector<std::string> list;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);

    return list;
}