#include "shell.h"

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
