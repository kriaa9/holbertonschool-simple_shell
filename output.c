#include "shell.h"

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
