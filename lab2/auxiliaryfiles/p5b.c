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
        
        printf("\nChild : Check child process state\n\n");
        printf("Child : Press any key to continue\n");
        char str[100];
        scanf("%s", str);
        printf("Child : Check child process state again\n");

    }
    else{
        printf("Parent : My process ID is:%d\n", getpid());
        printf("Parent : The child process ID is:%d\n", val);
        sleep(60);
        printf("Parent reaping child\n");
        wait(NULL);
    }
}