#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>

#define MLEN 2
#define msgtyp 3

struct message{
    long type;
    int  data[MLEN];
};

int main()
{
    key_t key;
    int msgid;
    message msg;

    key = ftok("msQ", 3);

    msgid = msgget(key, 0444 | IPC_CREAT);

    msgrcv(msgid, &msg, sizeof(message), msgtyp, 0);

    for(int i = 0; i < MLEN; i++){
        if(msg.data[i]==0)
            break;
        std::cout << msg.data[i]*3<<' ';
    }

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
