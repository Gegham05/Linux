#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define MAX_MSG_LEN 100

void send_message()
{
    char recipient[100], message[MAX_MSG_LEN + 1];
    printf("Enter the recipient's name: ");
    scanf("%s", recipient);
    getchar(); 
    
    printf("Enter a message (up to 100 characters): ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    if(strlen(message) == 0)
    {
        printf("Error: empty message.\n");
        return;
    }

    char sem_name[128], fifo_name[128];
    snprintf(sem_name, sizeof(sem_name), "/mailsem_%s", recipient);
    snprintf(fifo_name, sizeof(fifo_name), "/tmp/mailbox_%s", recipient);

    sem_t *sem = sem_open(sem_name, 0);
    if(sem == SEM_FAILED)
    {
        perror("Error: mailbox isn't initialized");
        return;
    }

    if(access(fifo_name, F_OK) != 0) 
    {
        printf("Error: the recipient is offline.\n");
        sem_close(sem);
        return;
    }

    sem_wait(sem);

    int fd = open(fifo_name, O_WRONLY | O_NONBLOCK);
    if(fd == -1)
    {
        perror("FIFO opening error");
        sem_post(sem);
        sem_close(sem);
        return;
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", tm_info);

    char sender[100];
    getlogin_r(sender, sizeof(sender));

    char full_message[512];
    snprintf(full_message, sizeof(full_message), "%s From %s: %s\n", timestamp, sender, message);

    write(fd, full_message, strlen(full_message));
    close(fd);

    sem_post(sem);
    sem_close(sem);
}

int main()
{
    int choice;
    while(1)
    {
        printf("\nWelcome to PipeMail!\n");
        printf("1. Send a message\n");
        printf("2. Exit\n");
        printf("Select the option: ");
        scanf("%d", &choice);

        if(choice == 1)
       	{
            send_message();
        }
       	else if(choice == 2)
       	{
            break;
        }
       	else
       	{
            printf("Wrong choice.\n");
        }
    }

    return 0;
}
