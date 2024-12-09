#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char** argv){
    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_RDONLY);
    int fd3 = open(argv[3], O_WRONLY);
    char buff[100];
    int size;
    while ((size = read(fd1, buff, sizeof(buff))) > 0){
        write(fd3, buff, size);
    }
    lseek(fd3, atoi(argv[4]), 0);
    while ((size = read(fd2, buff, sizeof(buff))) > 0){
        write(fd3, buff, size);
    }

    close(fd1);
    close(fd2);
    close(fd3);
}