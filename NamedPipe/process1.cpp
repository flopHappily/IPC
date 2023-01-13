#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

int main()
{
    int fd;
    char  *myfifo = "/tmp/myfifo"; // path to file
    mkfifo(myfifo, 0666); // 6 = 110 | read-write-execute | owner-group-other
    int a,b;

    fd = open(myfifo, O_WRONLY);
    std::cin >> a;
    while(a!=0){
        std::cout<<"Wrote: " << a << '\n';
        write(fd, &a, sizeof(int));
        close(fd);
        fd = open(myfifo, O_RDONLY);
        read(fd, &b, sizeof(b));
        std::cout<<"Read: " << b << '\n';
        close(fd);

        fd = open(myfifo, O_WRONLY);
        std::cin >> a;
    }
    write(fd, &a, sizeof(int));
    close(fd);
    return 0;
}