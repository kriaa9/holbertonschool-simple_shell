#include "shell.h"

/**
 * _getenv - gets environment variable value
 * @name: name of environment variable
 *
 * Return: pointer to value, NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	int name_len;

	if (name == NULL)
		return (NULL);

	name_len = _strlen(name);

	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], name, name_len) == 0)
		{
			if (environ[i][name_len] == '=')
				return (environ[i] + name_len + 1);
		}
		i++;
	}

	return (NULL);
}

/**
 * _which - finds command in PATH
 * @cmd: command to find
 *
 * Return: full path to command, NULL if not found
 */
char *_which(char *cmd)
{
	char *path_env, *path_copy, *path_token;
	char full_path[1024];
	struct stat st;

	if (cmd == NULL)
		return (NULL);

	if (_strchr(cmd, '/') != NULL)
	{
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}

	path_env = _getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	path_copy = _strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	path_token = strtok(path_copy, ":");
	while (path_token != NULL)
	{
		_strcpy(full_path, path_token);
		_strcat(full_path, "/");
		_strcat(full_path, cmd);

		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (_strdup(full_path));
		}

		path_token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * _strtok - tokenizes a string
 * @str: string to tokenize
 * @delim: delimiters
 *
 * Return: array of tokens, NULL if failure
 */
char **_strtok(char *str, const char *delim)
{
	char **tokens;
	char *token;
	int token_count = 0;
	char *str_copy;

	if (str == NULL || delim == NULL)
		return (NULL);

	str_copy = _strdup(str);
	if (str_copy == NULL)
		return (NULL);

	token = strtok(str_copy, delim);
	while (token != NULL)
	{
		token_count++;
		token = strtok(NULL, delim);
	}

	tokens = malloc((token_count + 1) * sizeof(char *));
	if (tokens == NULL)
	{
		free(str_copy);
		return (NULL);
	}

	_strcpy(str_copy, str);
	token = strtok(str_copy, delim);
	token_count = 0;

	while (token != NULL)
	{
		tokens[token_count] = _strdup(token);
		if (tokens[token_count] == NULL)
		{
			free(str_copy);
			return (NULL);
		}
		token_count++;
		token = strtok(NULL, delim);
	}

	tokens[token_count] = NULL;
	free(str_copy);

	return (tokens);
}

/**
 * execute_command - executes a command
 * @args: command and arguments
 *
 * Return: void
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (args == NULL || args[0] == NULL)
		return;

	if (_strcmp(args[0], "exit") == 0)
		exit(0);

	if (_strcmp(args[0], "cd") == 0)
	{
		if (chdir(args[1] == NULL ? getenv("HOME") : args[1]) == -1)
			perror("chdir");
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		cmd_path = _which(args[0]);
		if (cmd_path == NULL)
		{
			fprintf(stderr, "hsh: 1: %s: not found\n", args[0]);
			exit(127);
		}

		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execve");
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
