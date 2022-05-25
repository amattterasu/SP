#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(-1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Error! No port!" << endl;
        exit(-1);
    }

    const int PORT = atoi(argv[1]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    bzero((char *)&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Cвязывание сокета c портом и адресом
    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        error("Binding ERROR!");
    }

    // Режим ожидания сокета
    if (listen(sockfd, 5) == -1)
    {
        error("Listen ERROR!");
    }

    struct sockaddr_in client_address;
    socklen_t client_length = sizeof(client_address);
    char buffer[256];
    int message_by_client;

    cout << "Waiting for input..." << endl
         << endl;

    int connfd = accept(sockfd, (sockaddr *)&client_address, &client_length);
    if (connfd == -1)
    {
        error("ERROR on accept request");
    }
    while (true)
    {
        bzero(buffer, sizeof(buffer));
        // Чтение данных из сокета
        message_by_client = recv(connfd, buffer, sizeof(buffer), 0);

        if (message_by_client == -1)
        {
            error("ERROR on recieve message");
        }
        cout << "Message from client: " + string(buffer) << endl;

        if (strncmp("exit", buffer, 4) == 0)
        {
            string exit_message = "Server exiting...";
            cout << exit_message << endl;

            if (send(connfd, exit_message.c_str(), sizeof(exit_message), 0) == -1)
            {
                error("Sending message ERROR!");
            }
            break;
        }

        if (send(connfd, "message received.\n", 19, 0) == -1)
            error("ERROR on sending message");
    }

    close(connfd);
    close(sockfd);

    return 0;
}