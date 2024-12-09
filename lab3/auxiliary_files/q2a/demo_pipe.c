#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

/* Splits the string by space and returns the array of tokens
*
*/
char **tokenize(char *line) {

    // tokenizer variables
	char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
	char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
	int i, tokenIndex = 0, tokenNo = 0;

    // loop on length of line
	for(i=0; i < strlen(line); i++){

		char readChar = line[i];

        // tokenize on any kind of space
		if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
			token[tokenIndex] = '\0';
			if (tokenIndex != 0) {
				tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
				strcpy(tokens[tokenNo++], token);
				tokenIndex = 0; 
			}
		}
		else {
			token[tokenIndex++] = readChar;
		}
	}
    char readChar = line[i];
    if (readChar == '\0'){
        token[tokenIndex] = '\0';
        if (tokenIndex != 0) {
            tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
            strcpy(tokens[tokenNo++], token);
            tokenIndex = 0; 
        }
    }
	free(token);
	tokens[tokenNo] = NULL ;
	return tokens;
}
int main(int argc, char* argv[]) {
    if(argc!=2){
        printf("Please, enter the command in a quotes\n");
        return 0;
    }
    char line[100];
    strcpy(line,argv[1]);

    char *command = strtok(line, "|");
    char **comm1 = tokenize(command);
    command = strtok(NULL, "|");
    char **comm2 = tokenize(command);


    int pd[2];
    pipe(pd);
    // Write your code here
    // ---------------------------------------
    if (fork() == 0){
        dup2(pd[1], 1);
        close(pd[0]);
        close(pd[1]);
        execvp(comm1[0], comm1);
    }
    else{
        if (fork() == 0){
            dup2(pd[0], 0);
            close(pd[0]);
            close(pd[1]);
            execvp(comm2[0], comm2);
        }
    }



    // ---------------------------------------
    close(pd[0]);
    close(pd[1]);
    //Uncomment these lines after forking two processes
    wait(NULL);
    wait(NULL);
    return 0;
}