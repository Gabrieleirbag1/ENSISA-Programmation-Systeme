#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct msg {
    long mtype;
    char data[256];
};

void traite(char *data) {
    printf("-%s \n", data);
}

int main() {
    key_t key = ftok("toto", 'E');
    int msgid = msgget(key, IPC_CREAT | 0666);
    struct msg msg;

    while (1) {
        int received = 0;
        if (msgrcv(msgid, &msg, sizeof(msg.data), 1, IPC_NOWAIT) != -1) {
            received = 1;
        } else if (msgrcv(msgid, &msg, sizeof(msg.data), 2, IPC_NOWAIT) != -1) {
            received = 1;
        } else if (msgrcv(msgid, &msg, sizeof(msg.data), 3, IPC_NOWAIT) != -1) {
            received = 1;
        }

        if (received) {
            if (strlen(msg.data) == 0) break;
            traite(msg.data);
        }
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}