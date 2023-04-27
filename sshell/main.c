#include "shell.h"
/**
 * @ac: total sum of arguments
 * @argv: array of arguments
 * Return: Returns 0
 */
int main(int ac, char **argv)
{
	char username[10] = "tunde";
	char *userinput;
	size_t n = 0;
	char *userinput_copy = NULL; /*copy of string to be passed to strtok*/
	char *prompt = "root@";
	char *delimiter = " \n";
	size_t total_chars;
	int num_tokens = 0;
	char *token;
	int status, i;
	pid_t child_pid;
	(void)ac;
	/*printing a prompt*/
	while (1)
	{
		printf("%s%s:$ ", prompt, username);
		/*reading and printing user input using getline() function*/
		total_chars = getline(&userinput, &n, stdin);
		size_t newlen = strlen(userinput) + strlen("/usr/bin") + 1;
		char *newlineptr = malloc(newlen * sizeof(char));

		strcpy(newlineptr, "/usr/bin");
		strcat(newlineptr, userinput);
		userinput = newlineptr;
		if (total_chars == -1)
		{
			printf("Now Exiting the shell......\n");
			return (-1);
		}
		/*Allocate space for a copy of the userinput*/
		userinput_copy = malloc(sizeof(char) * total_chars);
		if (userinput_copy == NULL)
		{
			perror("tsh: Memory allocation Error");
			return (-1);
		}
		/*copy userinput to userinput_copy*/
		strcpy(userinput_copy, userinput);
		/*split userinput into tokens*/
		token = strtok(userinput, delimiter);
		while (token != NULL)
		{
			num_tokens++;
		}
		num_tokens++;
		argv = malloc(sizeof(char *) * num_tokens);
		token = strtok(userinput_copy, delimiter);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delimiter);
		}
		argv[i] = NULL;
		/*Implementing the child processes*/
		child_pid = fork();
		if (child_pid == -1)
		{
			free(userinput);
			return (-1);
		}
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Error");
			}
		}
		else
		{
			wait(&status);
		}
		free(newlineptr);
		free(userinput_copy);
		free(argv);
	}
	free(userinput);
	return (0);
}



