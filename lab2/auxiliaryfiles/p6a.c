#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>


void recursive(int n){
    int val = 0, children = 1;
    while (val == 0 && children <= n){
        if (children == n){
            printf("Child %d with parent %d exited\n", getpid(), getppid());
            break;
        }
        val = fork();
        children++;
        if (val == 0){
            printf("Child %d is created\n", getpid());
        }
        else{
            wait(NULL);
            printf("Child %d of parent %d exited\n", getpid(), getppid());
        }
    }
}

int main(int argv, char** argc){
    int n = atoi(argc[1]);
    printf("Parent is : %d\n", getpid());
    printf("Number of children: %d\n", n);
    int val = fork();
    if (val == 0){
        printf("Child %d is created\n", getpid());
        recursive(n);
    }
    else{
        wait(NULL);
        printf("Parent exited\n");
    }
}