#include "shell.h"

/**
 * build_path - builds the full path of the command
 * @dir: directory in the PATH
 * @command: command to search for
 * Return: full path of the command
 */
char *build_path(char *dir, char *command)
{
	char *path;
	size_t dir_len, command_len;

	dir_len = strlen(dir);
	command_len = strlen(command);

	path = malloc(dir_len + command_len + 2);
	if (path == NULL)
	{
		perror("Path");
		exit(1);
	}
	strcpy(path, dir);
	strcat(path, "/");
	strcat(path, command);
	strcat(path, "\0");
	return (path);
}

/**
 * find_command - finds the command in the PATH
 * @command: command to search for
 * Return: full path of the command if found, NULL otherwise
 */
char *find_command(char *command)
{
	char *path, *path_cpy;
	char *token, *full_path;
	struct stat buff;

	path = getenv("PATH");
	if (path == NULL || command == NULL)
	{
		return (NULL);
	}
	path_cpy = strdup(path);
	if (path_cpy == NULL)
	{
		perror("Path_cpy");
		exit(1);
	}
	token = strtok(path_cpy, ":");
	while (token != NULL)
	{
		full_path = build_path(token, command);
		if (stat(full_path, &buff) == 0)
		{
			free(path_cpy);
			return (full_path);
		}
		else
		{
			free(full_path);
			token = strtok(NULL, ":");
		}
	}
	free(path_cpy);
	if (stat(command, &buff) == 0)
	{
		return (command);
	}
	return (NULL);
}
