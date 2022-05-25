#include <iostream>
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
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);

    // Соединение с сервером
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        error("Connecting ERROR!");
    };

    char buffer[256];

    int msg_to_server, msg_from_server;

    while (true)
    {
        cout << "Enter a message: ";
        bzero(buffer, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);

        msg_to_server = send(sockfd, &buffer, sizeof(buffer), 0);

        if (msg_to_server == -1)
        {
            error("ERROR on writing to socket.");
        }

        msg_from_server = recv(sockfd, &buffer, sizeof(buffer), 0);

        cout << "Message from server: " + string(buffer) << endl;

        if (strncmp("Server exit...", buffer, 15) == 0)
        {
            cout << "Connection is closed..." << endl;
            break;
        }
    }

    close(sockfd);

    return 0;
}