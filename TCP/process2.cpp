#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#define port 8080

int main()
{
    char msg[128] = "Hello, Process1!";
    msg[127] = 0;
    int number = 99;
    int code;
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // AF_INET - IPv4, SOCK_STREAM - TCP, 0 - for default protocol (IP)

    sockaddr_in address;
    address.sin_family = AF_INET; // IPv4 address family
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // converst string to network bits | 127.0.0.1 - localhost
    address.sin_port = htons(port);

    code = connect(sockfd,(sockaddr*)&address,sizeof(address));
    if(code){
        std::cout << "Server is down\n";
        return 1;
    }

    std::cin >> number;
    send(sockfd,&number,sizeof(int),0);
    recv(sockfd,&number,sizeof(int),0);
    std::cout<< number;
    close(sockfd);

    return 0;
}
