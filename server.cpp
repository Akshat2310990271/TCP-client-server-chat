#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&address, sizeof(address));
    listen(serverSocket, 1);
    cout << "Waiting for client on port 8080...\n";

    int client = accept(serverSocket, nullptr, nullptr);
    char buffer[1024]{};

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(client, buffer, sizeof(buffer)-1, 0);
        if (bytes <= 0) break;

        cout << "Client: " << buffer << endl;
        if (string(buffer) == "exit") break;

        string reply = "Server received: " + string(buffer);
        send(client, reply.c_str(), reply.size(), 0);
    }

    close(client);
    close(serverSocket);
    return 0;
}
