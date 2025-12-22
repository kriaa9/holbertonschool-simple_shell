#include "shell.h"

#define TOKEN_DELIM " \t\n"

/**
 * shell_loop - main loop for shell execution
 *
 * Return: void
 */
void shell_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(1, "($) ", 4);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			if (interactive)
				write(1, "\n", 1);
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		args = _strtok(line, TOKEN_DELIM);

		if (args != NULL)
		{
			execute_command(args);
			free(args);
		}
	}

	if (line != NULL)
		free(line);
}
