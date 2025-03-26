#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include <sys/types.h>

void ping_signaler()
{
    int ping_fd, pong_fd;
    char buffer[20];
    ping_fd = open("/tmp/ping_fifo", O_WRONLY);
    pong_fd = open("/tmp/pong_fifo", O_RDONLY);

    while(true)
    {
        write(ping_fd, "PING", 5);
        std::cout << "ping_signaler: PING" << std::endl;
        read(pong_fd, buffer, sizeof(buffer));
        std::cout << "ping_signaler received: " << buffer << std::endl;
        sleep(1);
    }
    close(ping_fd);
    close(pong_fd);
}

void pong_signaler()
{
    int ping_fd, pong_fd;
    char buffer[20];
    ping_fd = open("/tmp/ping_fifo", O_RDONLY);
    pong_fd = open("/tmp/pong_fifo", O_WRONLY);

    while(true)
    {
        read(ping_fd, buffer, sizeof(buffer));
        std::cout << "ping_signaler received: " << buffer << std::endl;
        write(pong_fd, "PONG", 5);
        std::cout << "pong_signaler: PONG" << std::endl;
        sleep(1);
    }
    close(ping_fd);
    close(pong_fd);
}

int main()
{
    mkfifo("/tmp/ping_fifo", 0666);
    mkfifo("/tmp/pong_fifo", 0666);

    pid_t pid = fork();

    if (pid == 0) pong_signaler();
    else ping_signaler();

    return 0;
}

