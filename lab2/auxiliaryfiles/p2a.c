/*
Write a program p2a.c 
It takes an integer n from the console and prints the process pid and numbers from 1 to 2*n in any order
such that :
the child prints its pid and the numbers from 1 to n  and parent prints its pid and numbers from n+1 to 2*n .
Input : 3
Desired Sample output :
3451 1
3451 2
3448 4
3451 3
3448 5
3448 6   
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int n ;
    scanf("%d",&n);

    // write your code here
    int val = fork();

    if (val == 0){
        for (int i = 1; i <= n; i++){
            printf("C %d %d\n", getpid(), i);
        }
    }
    else{
        for (int i = n + 1; i <= 2 * n; i++){
            printf("P %d %d\n", getpid(), i);
        }
    }

    return 0;
}
