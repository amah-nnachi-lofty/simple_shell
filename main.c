#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>

/**
 * get_line - Read a line from standard input
 *
 * Return: A pointer to the read line (including the newline character),
 *         or NULL if an error occurs or end of file is reached
 */
char *get_line(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	write(STDOUT_FILENO, "$ ", 2);  /* Display the prompt */

	nread = getline(&buffer, &bufsize, stdin);
	if (nread == -1)
	{
		if (buffer != NULL)
			free(buffer);  /* Free the buffer if it was allocated */
		if (nread == 0)
		{
			return (NULL);  /* Reached end of file */
		}
		perror("getline");
		exit(EXIT_FAILURE);
	}

	return (buffer);
}

/**
 * execute_child - Execute the child process
 *
 * @command: Command to execute
 */
void execute_child(const char *command)
{
	char *args[2];  /* Only one argument */

	args[0] = strdup(command);
	args[1] = NULL;

	execvp(args[0], args);
	perror("execvp");
	exit(EXIT_FAILURE);
}

/**
 * execute_parent - Execute the parent process
 *
 * @child_pid: PID of the child process
 * @command: Command to execute
 */
void execute_parent(pid_t child_pid, const char *command)
{
	int status;

	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		const char *error_message = "Command exited with non-zero status: ";

		write(STDOUT_FILENO, error_message, strlen(error_message));
		write(STDOUT_FILENO, command, strlen(command));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * execute_command - Execute the given command
 *
 * @command: Command to execute
 */
void execute_command(const char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execute_child(command);
	}
	else
	{
		execute_parent(pid, command);
	}
}

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
	char *command;

	while (1)
	{
		command = get_line();
		if (command == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);  /* Add a new line before exiting */
			break;
		}

		/* Remove the trailing newline character */
		command[strcspn(command, "\n")] = '\0';

		execute_command(command);

		free(command);
	}

	return (0);
}


