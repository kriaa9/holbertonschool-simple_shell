#include "shell.h"

/**
 * main - Simple Shell 0.3
 * @ac: Argument count
 * @av: Argument vector
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
	char *args[1024];
	char *token, *command_path;
	int i, loop_count = 0; /* Loop counter for error messages */

	(void)ac;

	while (1)
	{
		loop_count++; /* Increment line number */

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
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		i = 0;
		token = strtok(line, " \n\t");
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " \n\t");
		}
		args[i] = NULL;

		if (i == 0)
			continue;

		command_path = get_location(args[0]);
		
		/* If command is not found, print EXACT error format */
		if (command_path == NULL)
		{
			/* Format: ./hsh: 1: ls: not found */
			fprintf(stderr, "%s: %d: %s: not found\n", av[0], loop_count, args[0]);
			continue;
		}

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			continue;
		}
		if (child_pid == 0)
		{
			if (execve(command_path, args, environ) == -1)
			{
				perror(av[0]);
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
		free(command_path);
	}
	free(line);
	return (0);
}
