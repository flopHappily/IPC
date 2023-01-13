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

    while(true){
        if(NR->readNumber == false) continue;
        cout << "Read: " << NR->number  << '\n';
        NR->readNumber = false;
        if(NR->number == 0) break;
    };

    shmdt(NR); // detach
    shmctl(shmid,IPC_RMID, nullptr);  // destroy // IPC_RMID − Marks the segment to be destroyed.
    return 0;
}