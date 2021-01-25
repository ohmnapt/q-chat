#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include <signal.h>

//นายณภัฒร์ สุวรรณศร
// 6113187 EGCO
struct my_msg
{
    long msg_type;
    char data[BUFSIZ];
};

int main(int argc, char *argv[])
{
    int child,nbytes, msgID;
    struct my_msg a_msg;
    long int rxcv_msg_type;
    char buffer[BUFSIZ]= "";

    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s <[1, 2]\n",*argv);
        exit(EXIT_FAILURE);
    }


    msgID = msgget((key_t) 11235,0666 | IPC_CREAT);
    argv++;

    if(strcmp(*argv, "1") == 0)
    {

        child = fork();
        switch (child)
        {
        case -1 :
            perror("Forking failed");
            exit(EXIT_FAILURE);
        case 0 :
            while(strncmp(a_msg.data, "end chat", 8))
            {
                fgets(buffer, BUFSIZ,stdin);
                a_msg.msg_type = 1;
                strcpy(a_msg.data,buffer);
                if(msgsnd(msgID, (void*)&a_msg,BUFSIZ,0)== -1)
                {
                    fprintf(stderr,"msgsnd failed\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;
        default :
            while (strncmp(buffer, "end chat",8))
            {
                rxcv_msg_type = 2;
                if(msgrcv(msgID,(void*)&a_msg,BUFSIZ,rxcv_msg_type,0) == -1);
                {
                    fprintf(stderr,"msgrcv failed\n");
                    exit(EXIT_FAILURE);
                }
                printf("Data Recieved : %s\n",a_msg.data);
            }
        }

    }

    if(strcmp(*argv, "2") == 0)
    {

        child = fork();
        switch (child)
        {
        case -1 :
            perror("Forking failed");
            exit(EXIT_FAILURE);
        case 0 :
            while(strncmp(a_msg.data, "end chat", 8))
            {
                fgets(buffer, BUFSIZ,stdin);
                a_msg.msg_type = 2;
                strcpy(a_msg.data,buffer);
                if(msgsnd(msgID, (void*)&a_msg,BUFSIZ,0)== -1)
                {
                    fprintf(stderr,"msgsnd failed\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;
        default :
            while (strncmp(buffer, "end chat",8))
            {
                rxcv_msg_type = 1;
                if(msgrcv(msgID,(void*)&a_msg,BUFSIZ,rxcv_msg_type,0) == -1);
                {
                    fprintf(stderr,"msgrcv failed\n");
                    exit(EXIT_FAILURE);
                }
                printf("Data Recieved : %s\n",a_msg.data);
            }
        }


    }
}
