#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

int main() {
    int client = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    if (connect(client, (sockaddr*)&address, sizeof(address)) < 0) {
        cerr << "Connection failed.\n";
        return 1;
    }

    string message;
    char buffer[1024]{};

    while (true) {
        cout << "> ";
        getline(cin, message);
        send(client, message.c_str(), message.size(), 0);
        if (message == "exit") break;

        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(client, buffer, sizeof(buffer)-1, 0);
        if (bytes <= 0) break;
        cout << buffer << endl;
    }

    close(client);
    return 0;
}
