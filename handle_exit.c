#include "shell.h"

/**
 * handle_exit - handle arguments for the built-in exit
 * @command: command parameter
 * @av: argement vector
 * Return: 0 on success
 */
void handle_exit(char *command, char **av)
{
	int status;

	status = 0;
	if (av[1] != NULL)
	{
		status = atoi(av[1]);
	}
	cleaner(av);
	cleanup(command, av);
	exit(status);
}
