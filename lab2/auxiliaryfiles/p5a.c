#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
    int val = fork();
    if (val == 0){
        printf("Child : My process ID is:%d\n", getpid());
        printf("Child : The parent process ID is:%d\n", getppid());
        sleep(5);
        printf("Child : After sleeping for 5 seconds\n");
        printf("Child : My process ID is:%d\n", getpid());
        printf("Child : The parent process ID is:%d\n", getppid());
    }
    else{
        printf("Parent : My process ID is:%d\n", getpid());
        printf("Parent : The child process ID is:%d\n", val);
        sleep(1);
    }
}