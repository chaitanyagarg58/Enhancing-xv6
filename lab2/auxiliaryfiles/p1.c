#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
    int val = fork();
    if (val == 0){
        printf("My process ID is:%d\n", getpid());
        printf("The parent process ID is:%d\n", getppid());
    }
    else{
        printf("My process ID is:%d\n", getpid());
        printf("The child process ID is:%d\n", val);
    }
}