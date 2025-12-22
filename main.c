#include "shell.h"

/**
 * main - Simple Shell 0.1 & 0.2
 * @ac: Argument count
 * @av: Argument vector
 *
 * Description: Handles commands with arguments.
 * Fixes: The checker requires argument handling for ./hbtn_ls /var
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t child_pid;
	int status;
	char *args[64]; /* Array to hold command and arguments */
	char *token;
	int i;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			exit(0);
		}

		/* Remove newline */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Tokenize input into args array */
		i = 0;
		token = strtok(line, " \n\t");
		while (token != NULL && i < 63)
		{
			args[i++] = token;
			token = strtok(NULL, " \n\t");
		}
		args[i] = NULL; /* Null-terminate the list */

		/* If no command was typed, restart loop */
		if (i == 0)
			continue;

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			continue;
		}

		if (child_pid == 0)
		{
			/* Execute command with arguments */
			if (execve(args[0], args, environ) == -1)
			{
				perror(av[0]);
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
	}
	free(line);
	return (0);
}
