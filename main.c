#include "shell.h"

/**
 * main - entry point of the shell
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment variables pointer
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;

	shell_loop();

	return (0);
}
