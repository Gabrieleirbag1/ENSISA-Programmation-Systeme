#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct msg
{
    int priority;
    char data[256];
};

int main(int argc, char *argv[])
{
    key_t key = ftok("toto", 'E');
    int msgid = msgget(key, 0);
    struct msg msg;

    if (argc == 1)
    {
        msg.priority = 1;
        strcpy(msg.data, "");
    }
    else if (argc == 3)
    {
        msg.priority == 3;
        strcpy(msg.data, argv[2]);
    }
    else
    {
        printf("Usage: %s [priority str]\n", argv[0]);
        return 1;
    }

    if (msgsnd(msgid, &msg, sizeof msg.data, 0) == -1)
    {
        perror("msgsnd failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}