// Client side C/C++ program to demonstrate Socket programming
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <iostream>

#define PORT 8080

int main() {

}

int runClient(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0;
    ssize_t valread;
    struct sockaddr_in serv_addr;

    std::string hello = "Hello from client ";
    hello += argv[2];

    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    for (int i = 0; i < 5; ++i) {
        memset(buffer, 0, 1024);
        send(sock , hello.c_str(), hello.length(), 0 );
        printf("Hello message sent\n");
        valread = read( sock , buffer, 1024);
        std::cout << buffer << " " << valread << std::endl;
        printf("%s\n",buffer);
        sleep(2);
    }

    return 0;
}
