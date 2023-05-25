#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

/**
 * struct my_builtin_s - struct define
 * @name: character
 * @f: integer
 */

typedef struct my_builtin_s
{
	char *name;
	int (*f)(char **av);
} builtin_t;

extern char **environ;

char *_strpbrk(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);
int _strlen(const char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_memcpy(char *dest, const char *src, unsigned int n);
char *_strdup(const char *s);

void handle_interrupt(int signum);
void prompt(void);
char *read_cmd(void);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char  **_tokenize(char *command, char *delim);
char *find_command(char *command);
char *build_path(char *dir, char *command);
void shell_loop(char **av, char **env);
void exe_cmd1(char *command, char **av, char **env);
void executor(char *command, char **av, char **env);
void execute_command(char *command, char **av, char **env);
void cleanup(char *command, char **av);
void execute_exit(void);
void print_env(char **env);
void cleaner(char **temp);
void handle_exit(char *command, char **av);
void process_command(char *command, char **av, char **env);

#endif
