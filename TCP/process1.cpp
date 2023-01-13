#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#define port 8080


int main()
{
    char msg[128];
    int msgSize;
    int number = 8;
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // AF_INET - IPv4, SOCK_STREAM - TCP, 0 - for default protocol (IP)

    sockaddr_in address;
    address.sin_family = AF_INET; // IPv4 address family
    address.sin_addr.s_addr = htonl(INADDR_ANY); // htonl converst int from host bite to network bite | INADDR_ANY - any incoming connection
    address.sin_port = htons(port);

    bind(sockfd,(sockaddr*)&address,sizeof(address)); // binds socket to port from address

    listen(sockfd,128);

    /*---RUNNING---*/
    socklen_t size;
    int clientSocket;
    for(;;){
        size = sizeof(address);
        clientSocket =  accept(sockfd,(sockaddr*)&address,&size); // waiting for connection, assigning new socket when connected
        msgSize = recv(clientSocket,&number,sizeof(int),0);
        number*=3;
        send(clientSocket,&number,sizeof(int),0);
        printf("%d\n",number);
        close(clientSocket);
    }
    close(sockfd);
}
