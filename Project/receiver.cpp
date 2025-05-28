#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>

char fifo_name[128], sem_name[128];
int fd;
sem_t *sem;

void cleanup(int signum)
{
    (void)signum;
    close(fd);
    unlink(fifo_name);
    sem_close(sem);
    sem_unlink(sem_name);
    printf("\nMailbox is closed. Exit.\n");
    exit(0);
}

int main(int argc, char *argv[]) 
{
    if(argc != 3 || strcmp(argv[1], "--receive") != 0)
    {
        printf("Usage: %s --receive <username>\n", argv[0]);
        return 1;
    }

    char *username = argv[2];
    snprintf(fifo_name, sizeof(fifo_name), "/tmp/mailbox_%s", username);
    snprintf(sem_name, sizeof(sem_name), "/mailsem_%s", username);

    mkfifo(fifo_name, 0666);
    sem = sem_open(sem_name, O_CREAT, 0666, 1);

    if(sem == SEM_FAILED)
    {
        perror("sem_open");
        return 1;
    }

    signal(SIGINT, cleanup);

    printf("Mailbiox %s opened. Message waiting...\n", username);
    fd = open(fifo_name, O_RDONLY);

    char buffer[512];
    while(1)
    {
        ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
        if(bytes > 0)
       	{
            buffer[bytes] = '\0';
            printf("%s", buffer);
        }
    }

    return 0;
}
