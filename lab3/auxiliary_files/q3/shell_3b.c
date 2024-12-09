#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// You may assume that the input command has no more than 1024 characters, and no more than 64 “tokens”. Further, you may assume that each token is no longer than 64 characters.
#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

/* Splits the string by space and returns the array of tokens
 *
 */
char **tokenize(char *line)
{
	char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
	char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
	int i, tokenIndex = 0, tokenNo = 0;

	for (i = 0; i < strlen(line); i++)
	{

		char readChar = line[i];

		if (readChar == ' ' || readChar == '\n' || readChar == '\t')
		{
			token[tokenIndex] = '\0';
			if (tokenIndex != 0)
			{
				tokens[tokenNo] = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
				strcpy(tokens[tokenNo++], token);
				tokenIndex = 0;
			}
		}
		else
		{
			token[tokenIndex++] = readChar;
		}
	}

	free(token);
	tokens[tokenNo] = NULL;
	return tokens;
}

void sig_int(int sig){
	printf("\nRECEIVED SIGNAL: %i\n", sig);
}

/* THE MAIN FUNCTION */
int main(int argc, char *argv[])
{
	char line[MAX_INPUT_SIZE];
	char **tokens;
	int i;
	signal(SIGINT, sig_int);

	while (1)
	{
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		printf("$ ");
		scanf("%[^\n]", line);
		getchar();

		// printf("Command ente	red: '%s' (REMOVE THIS OUTPUT LATER)\n", line);
		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; // terminate with new line
		tokens = tokenize(line);

		if (tokens[0] == NULL)	// if empty command, ask for as command again in new line
            continue;

		// Printing each found token in a new line for debugging
		// for (i = 0; tokens[i] != NULL; i++)
		// {
		// 	printf("Found the #%d token: '%s' (REMOVE THIS OUTPUT LATER)\n", i, tokens[i]);
		// }

		/* 
			WRITE YOUR CODE HERE
		*/
		if (fork() == 0){
			execvp(tokens[0], tokens);
		}
		else{
			wait(NULL);
		}

		// Freeing the allocated memory to the tokens
		for (i = 0; tokens[i] != NULL; i++)
		{
			free(tokens[i]);
		}
		free(tokens);
	}
	return 0;
}