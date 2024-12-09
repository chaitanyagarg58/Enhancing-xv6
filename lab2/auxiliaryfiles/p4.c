#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    // Do exec here
    int x;
    printf("Process A : Input value of x : ");
    scanf("%d", &x);
    
    int fd[2];
    pipe(fd);

    int val = fork();

    if (val == 0){
        int y;
        printf("Process B : Input value of y : ");
        scanf("%d", &y);
        int sum = x + y;
        char sum_str[20];
        snprintf(sum_str, 20, "%d", sum);

        write(fd[1], sum_str, 20);
    }
    else{
        char sum_str[20];
        read(fd[0], sum_str, 20);
        int sum = atoi(sum_str);
        printf("Process A : Result after addition : %d\n", sum);
    }

    return 0;
}