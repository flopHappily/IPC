#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    int a,b;

    fd = open(myfifo,O_RDONLY);
    read(fd, &a, sizeof(int));
    while(a!=0){
        std::cout << "Read: " << a <<'\n';
        close(fd);

        b = a*3;
        fd = open(myfifo,O_WRONLY);
        write(fd, &b, sizeof(int));
        std::cout << "Wrote: " << b << '\n';
        close(fd);

        fd = open(myfifo,O_RDONLY);
        read(fd, &a, sizeof(int));
    }
    close(fd);
    return 0;
}