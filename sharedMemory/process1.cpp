#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;

struct numberReader{
    int number;
    bool readNumber;
};

int main()
{
    int temp;
    key_t key = ftok("memory",3);

    int shmid = shmget(key,sizeof(int)+sizeof(bool),0666|IPC_CREAT);

    numberReader *NR = (numberReader*) shmat(shmid,(void*)0,0);

    cout<<"Write: ";
    cin >> temp;
    NR->number = temp;
    NR->readNumber = true;

    while(temp!=0){
        if(NR->readNumber) continue;
        cout <<"Write: ";
        cin >> temp;
        NR->number = temp;
        NR->readNumber = true;
    };

    shmdt(NR); // detach
    return 0;
}