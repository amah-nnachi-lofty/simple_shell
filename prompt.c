#include "shell.h"

#define PROMPT "#cisfun$ "

/**
 * prompt - prompts the user for input
 * Return: void
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
	}
}
