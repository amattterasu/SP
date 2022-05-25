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

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_address;
    bzero((char *)&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        error("Binding ERROR!");
    }

    char buffer[256];
    int message;
    struct sockaddr_in client_address;
    bzero((char *)&client_address, sizeof(client_address));
    socklen_t client_length = sizeof(client_address);

    cout << "Waiting for input..." << endl
         << endl;

    while (true)
    {
        bzero(buffer, sizeof(buffer));
        message = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                           (struct sockaddr *)&client_address,
                           &client_length);

        if (message == -1)
        {
            error("ERROR on recieve message");
        }
        cout << "Message from client: " + string(buffer) << endl;

        if (strncmp("exit", buffer, 4) == 0)
        {
            string exit_message = "Server exiting...";
            cout << exit_message << endl;

            if (sendto(sockfd, exit_message.c_str(), sizeof(exit_message), 0, (const struct sockaddr *)&client_address, client_length) == -1)
            {
                error("ERROR on sending message");
            }
            break;
        }

        if (sendto(sockfd, "message received.\n", 19, 0,
                   (const struct sockaddr *)&client_address,
                   client_length) == -1)
            error("ERROR on sending message!");
    }

    close(sockfd);

    return 0;
}