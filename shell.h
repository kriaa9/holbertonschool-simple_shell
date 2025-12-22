#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

extern char **environ;

/* Function prototypes */
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, const char *src);
void _puts(const char *str);
int _strncmp(const char *s1, const char *s2, int n);
char *_strchr(const char *s, char c);
char *_getenv(const char *name);
char *_which(char *cmd);
char **_strtok(char *str, const char *delim);
void execute_command(char **args);
void shell_loop(void);

#endif
