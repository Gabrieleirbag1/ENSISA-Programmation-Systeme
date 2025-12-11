#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    mqd_t mq;
    char buffer[256];
    struct mq_attr attr;
    
    mq_unlink("/q");
    
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;
    attr.mq_curmsgs = 0;
    
    mq = mq_open("/q", O_CREAT | O_RDWR, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }
    
    pid_t p = fork();
    
    if (p == 0) 
    {
        int total = 0;
        int len;
        
        while (1)
        {
            len = mq_receive(mq, buffer, 256, NULL);
            if (buffer[0] == '\0') break;
            total += len - 1;
        }
        
        printf("Total octets reçus: %d\n", total);
        mq_close(mq);
        exit(0);
    }
    else
    {
        while (fgets(buffer, 256, stdin) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            mq_send(mq, buffer, strlen(buffer) + 1, 0);
        }
        
        mq_send(mq, "", 1, 0);
        
        wait(NULL);
        mq_close(mq);
        mq_unlink("/q");
    }
    
    return 0;
}