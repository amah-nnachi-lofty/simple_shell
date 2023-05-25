#include "shell.h"

/**
 * cleaner - free a double pointer to an array
 * @temp: double pointer to temp
 * Return: void
 */
void cleaner(char **temp)
{
	while (*temp != NULL)
	{
		free(*temp);
		temp++;
	}
}

/**
 * cleanup - frees up memory
 * @command: command to cleanup
 * @av: array to cleanup
 * Return: void
 */
void cleanup(char *command, char **av)
{
	if (command != NULL)
		free(command);
	free(av);
}
