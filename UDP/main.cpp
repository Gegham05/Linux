#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024

int sockfd;
sockaddr_in my_addr{}, peer_addr{};
socklen_t addr_len = sizeof(sockaddr_in);

void receive_messages()
{
    char buffer[BUF_SIZE];
    while(true)
    {
        ssize_t len = recvfrom(sockfd, buffer, BUF_SIZE - 1, 0, (sockaddr*)&peer_addr, &addr_len);
        if(len > 0)
       	{
            buffer[len] = '\0';
            std::cout << "[Peer]: " << buffer << std::endl;
            std::cout << ": " << std::endl;
        }
    }
}

void send_messages()
{
    std::string message;
    while(true) 
    {
        std::cout << ": ";
        std::getline(std::cin, message);
        if(!message.empty())
       	{
            sendto(sockfd, message.c_str(), message.length(), 0, (sockaddr*)&peer_addr, addr_len);
        }
    }
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <my_port> <peer_port>\n";
        return 1;
    }
    int my_port = std::stoi(argv[1]);
    int peer_port = std::stoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        perror("socket");
        return 1;
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(my_port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sockfd, (sockaddr*)&my_addr, sizeof(my_addr)) < 0)
    {
        perror("bind");
        return 1;
    }
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(peer_port);
    peer_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    std::thread recv_thread(receive_messages);
    std::thread send_thread(send_messages);
    recv_thread.join();
    send_thread.join();

    close(sockfd);
    return 0;
}
