#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

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

    int PORT = atoi(argv[1]);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);

    char buffer[256];

    int msg_to_server, msg_from_server;

    struct sockaddr_in client_address;
    bzero(&client_address, sizeof(client_address));
    socklen_t client_length = sizeof(client_address);

    while (true)
    {
        cout << "Enter a message: ";
        bzero(buffer, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);

        msg_to_server = sendto(sockfd, buffer, sizeof(buffer), 0,
                               (struct sockaddr *)&server_address,
                               client_length);

        if (msg_to_server == -1)
        {
            error("ERROR on writing to socket.");
        }

        bzero(buffer, sizeof(buffer)); 

        msg_from_server = recvfrom(sockfd, &buffer, sizeof(buffer), 0,
                                   (struct sockaddr *)&client_address,
                                   &client_length);

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