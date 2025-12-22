#include "shell.h"

#define BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\n"

/**
 * _strlen - returns the length of a string
 * @s: pointer to string
 *
 * Return: length of string
 */
int _strlen(const char *s)
{
	int len = 0;

	if (s == NULL)
		return (0);

	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * _strcpy - copies a string from src to dest
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to new string, NULL if failure
 */
char *_strdup(const char *str)
{
	char *new_str;
	int len;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);
	new_str = malloc((len + 1) * sizeof(char));

	if (new_str == NULL)
		return (NULL);

	_strcpy(new_str, str);

	return (new_str);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: difference between s1 and s2
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to dest
 */
char *_strcat(char *dest, const char *src)
{
	int dest_len = _strlen(dest);
	int i = 0;

	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 * _puts - prints a string followed by a newline
 * @str: string to print
 *
 * Return: void
 */
void _puts(const char *str)
{
	while (*str)
	{
		putchar(*str);
		str++;
	}
	putchar('\n');
}

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
 * _strncmp - compares first n bytes of two strings
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to compare
 *
 * Return: difference between strings
 */
int _strncmp(const char *s1, const char *s2, int n)
{
	int i = 0;

	while (i < n && s1[i] && s1[i] == s2[i])
		i++;

	if (i == n)
		return (0);

	return (s1[i] - s2[i]);
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
 * _strchr - locates a character in a string
 * @s: string to search
 * @c: character to find
 *
 * Return: pointer to first occurrence, NULL if not found
 */
char *_strchr(const char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}

	if (c == '\0')
		return ((char *)s);

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
