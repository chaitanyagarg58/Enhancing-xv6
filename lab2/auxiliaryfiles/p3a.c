#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    
    printf("Print statement before exec\n");
    
    // Do exec here
    char strs[100];
    scanf("%s", strs);

    char path[200], file[200];

    sprintf(path, "./%s.out", strs);
    sprintf(file, "%s.out", strs);

    execl(path, file, NULL);
    

    printf("Print statement after exec. This should never print\n");
    
    
    return 0;
}