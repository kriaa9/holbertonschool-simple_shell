#include "shell.h"

/**
 * get_location - Locates a command in the PATH directories
 * @command: The command to look for
 *
 * Return: Full path or NULL if not found
 */
char *get_location(char *command)
{
	char *path = NULL, *path_copy, *path_token, *file_path;
	int command_len, dir_len;
	struct stat buffer;
	int i = 0;

	/* * FIX: Only treat command as a path if it contains '/'
	 * If the user types "ls", we must NOT check the current dir
	 * unless PATH tells us to.
	 */
	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &buffer) == 0)
			return (strdup(command));
		return (NULL);
	}

	/* 2. Find PATH variable safely */
	if (!environ)
		return (NULL);

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
		i++;
	}

	/* If PATH is missing or empty, we can't find the command */
	if (!path || strlen(path) == 0)
		return (NULL);

	path_copy = strdup(path);
	command_len = strlen(command);

	/* 3. Search directories */
	path_token = strtok(path_copy, ":");
	while (path_token != NULL)
	{
		dir_len = strlen(path_token);
		file_path = malloc(command_len + dir_len + 2);
		
		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, command);

		if (stat(file_path, &buffer) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		free(file_path);
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
