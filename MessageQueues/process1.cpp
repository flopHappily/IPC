#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>

#define MLEN 2
#define msgtyp 3

struct message{
    long type = msgtyp;
    int  data[MLEN];
};

int main()
{
    key_t key;
    int msgid;
    message msg;

    key = ftok("msQ", 3);

    msgid = msgget(key, 0666 | IPC_CREAT);


    for(int i = 0; i < MLEN; i++)
        std::cin >> msg.data[i];

    msgsnd(msgid, &msg, sizeof(int) * MLEN, 0);

    return 0;
}