#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    int n = atoi(argv[1]);
    int root = getpid();
    printf("Parent is : %d\n", root);
    printf("Number of children: %d\n", n);
    
    for (int i = 0; i < n; i++){
        if (fork() == 0){
            printf("Child %d is created\n", getpid());
            sleep(1);
            printf("Child %d of parent %d exited\n", getpid(), getppid());
            return 0;
        }
    }
    while (wait(NULL) > 0);
    printf("Parent exited\n");
}