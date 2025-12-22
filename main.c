#include "shell.h"

/**
 * main - Simple Shell 0.1
 * @ac: Argument count
 * @av: Argument vector
 *
 * Description: A simple UNIX command interpreter.
 * Handles one-word commands and EOF (Ctrl+D).
 * Does not handle arguments or PATH yet.
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
	char *args[2]; /* args[0] = command, args[1] = NULL */

	(void)ac; /* Unused for now */

	while (1)
	{
		/* 1. Display Prompt (only in interactive mode) */
		if (isatty(STDIN_FILENO))
			printf("($) ");

		/* 2. Read Input */
		nread = getline(&line, &len, stdin);

		/* Handle EOF (Ctrl+D) or Error */
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			exit(0);
		}

		/* 3. Parse Input: Remove the newline character */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Skip empty lines (user just pressed Enter) */
		if (line[0] == '\0')
			continue;

		/* 4. Execution Phase */
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			continue;
		}

		if (child_pid == 0)
		{
			/* Child Process: Execute the command */
			args[0] = line;
			args[1] = NULL;

			if (execve(args[0], args, environ) == -1)
			{
				/* Error handling if command not found */
				perror(av[0]);
				exit(1); /* Child must exit on failure */
			}
		}
		else
		{
			/* Parent Process: Wait for child to finish */
			wait(&status);
		}
	}
	/* Cleanup (though the loop handles exit) */
	free(line);
	return (0);
}
