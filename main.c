#include "shell.h"

/**
 * main - Simple Shell 0.1
 * @ac: Argument count
 * @av: Argument vector
 *
 * Description: Handles one-word commands and EOF.
 * Fixes: Uses strtok to handle leading/trailing spaces and empty lines.
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
	char *command;

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

		/* Remove the newline character */
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Tokenize the line to remove spaces and get the command */
		/* The delimiters are space ( ), newline (\n), and tab (\t) */
		command = strtok(line, " \n\t");

		/* If the line was just spaces or empty, command is NULL */
		if (command == NULL)
			continue;

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			continue;
		}

		if (child_pid == 0)
		{
			args[0] = command;
			args[1] = NULL;

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
