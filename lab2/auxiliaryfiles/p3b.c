#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    // Do exec here
    while (1){
        char strs[100];
        printf(">>> ");
        scanf("%s", strs);

        char path[200], file[200];

        sprintf(path, "./%s.out", strs);
        sprintf(file, "%s.out", strs);

        int val = fork();

        if (val == 0){
            execl(path, file, NULL);   
        }
        else{
            wait(NULL);
        }
    }
    
    return 0;
}