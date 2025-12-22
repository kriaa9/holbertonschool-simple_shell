#include "shell.h"

/**
 * get_location - Locates a command in the PATH directories
 * @command: The command to look for (e.g., "ls")
 *
 * Return: A pointer to the full path (e.g., "/bin/ls") or NULL if not found.
 */
char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_len, dir_len;
	struct stat buffer;
	int i = 0;

	/* 1. Check if command contains '/' (already a path) */
	if (stat(command, &buffer) == 0)
		return (strdup(command));

	/* 2. Find the PATH environment variable */
	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5; /* Skip "PATH=" */
			break;
		}
		i++;
	}
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	command_len = strlen(command);

	/* 3. Loop through directories in PATH */
	path_token = strtok(path_copy, ":");
	while (path_token != NULL)
	{
		dir_len = strlen(path_token);
		file_path = malloc(command_len + dir_len + 2); /* +2 for '/' and null byte */
		
		/* Build the full path: dir + "/" + command */
		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, command);

		/* 4. Check if file exists */
		if (stat(file_path, &buffer) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		free(file_path);
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL); /* Not found */
}
