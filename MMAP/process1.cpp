#include <stdio.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <iostream>
#include <unistd.h>

#define MAX 2
#define SOURCE "./mapedFile"
#define COUNT 5

int main(){


    int fd = open(SOURCE,O_RDWR);
    int *ptr = (int*) mmap(NULL, MAX * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(ptr == MAP_FAILED)
        std::cout<<"Mapping Failed\n";
    ptr[0] = 0;
    for(int i = 0;i<COUNT;i++){
        while(ptr[0]==0){
            msync(ptr,MAX*sizeof(int),MS_SYNC);
        };
        for(int i=1; i < MAX; i++){
            ptr[i]*=3;  // change walues
        }
        printf("%d\n",ptr[1]);
        ptr[0] = 0;
        msync(ptr,MAX*sizeof(int),MS_INVALIDATE);
    }
    ptr[0] = 1;
    msync(ptr,MAX*sizeof(int),MS_INVALIDATE);
    munmap(ptr, MAX * sizeof(int));
    close(fd);
    return 0;
}