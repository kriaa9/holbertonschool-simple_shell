#include "shell.h"

/**
 * main - Simple Shell 1.0
 * @ac: Argument count
 * @av: Argument vector
 *
 * Description: Handles 'exit' and 'env' built-ins.
 * Return: 0 on success, or specific error code
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t child_pid;
	int status, exit_status = 0;
	char *args[1024];
	char *token, *command_path;
	int i, k, loop_count = 0;

	(void)ac;

	while (1)
	{
		loop_count++;
		if (isatty(STDIN_FILENO))
			printf("($) ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			return (exit_status);
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

		/* TASK 5: Handle "exit" built-in */
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			exit(exit_status);
		}

		/* TASK 6: Handle "env" built-in */
		if (strcmp(args[0], "env") == 0)
		{
			k = 0;
			while (environ[k])
			{
				printf("%s\n", environ[k]);
				k++;
			}
			exit_status = 0;
			continue; /* Skip fork, go to next prompt */
		}

		/* External command handling */
		command_path = get_location(args[0]);
		
		if (command_path == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", av[0], loop_count, args[0]);
			exit_status = 127;
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
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
		free(command_path);
	}
	free(line);
	return (exit_status);
}
