#include <stdio.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <iostream>

#define MAX 2
#define SOURCE "./mapedFile"
#define COUNT 5

int main(){

    int fd = open(SOURCE,O_RDWR);
    int *ptr = (int*) mmap(NULL, MAX * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(ptr == MAP_FAILED)
        std::cout<<"Mapping Failed\n";
    msync(ptr,MAX*sizeof(int),MS_SYNC);
    ptr[0] = 1;
    for(int i = 0;i<COUNT;i++){
        printf("WRITE VALUES:");
        for(int i=1; i < MAX; i++){
            std::cin >> ptr[i]; // write new data
        }

        ptr[0] = 1;
        msync(ptr,MAX*sizeof(int),MS_INVALIDATE);
        while(ptr[0]!=0){
            msync(ptr,MAX*sizeof(int),MS_SYNC);
        }
        printf("\nPROC1 UPDATES:");
        for (int i = 1; i < MAX; i++ ){
            printf(" %d", ptr[i] );
        }
        printf("\n");
    }
    munmap(ptr, MAX * sizeof(int));
    close(fd);
    return 0;
}