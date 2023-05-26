#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10

/**
 * parse_arguments - Parses the command line input into arguments
 * @input: The command line input string
 * @args: An array to store the parsed arguments
 */
void parse_arguments(char *input, char *args[])
{
    int i = 0;
    int arg_index = 0;
    int in_quote = 0;
    int quote_start = 0;
    int redirection_type = 0;
    char *redirection_file = NULL;

    while (input[i] != '\0')
    {
        if (input[i] == '"')
        {
            if (!in_quote)
            {
                in_quote = 1;
                quote_start = i + 1;
            }
            else
            {
                in_quote = 0;
                input[i] = '\0';  /* Replace closing quote with null character */
                args[arg_index] = &input[quote_start];
                arg_index++;
            }
        }
        else if (input[i] == ' ' && !in_quote)
        {
            input[i] = '\0';  /* Replace space with null character */
        }
        else if (input[i] == '<' && !in_quote)
        {
            input[i] = '\0';  /* Replace input redirection symbol with null character */
            redirection_type = 1;  /* Set redirection type to input */
            redirection_file = &input[i + 1];
        }
        else if (input[i] == '>' && !in_quote)
        {
            input[i] = '\0';  /* Replace output redirection symbol with null character */
            redirection_type = 2;  /* Set redirection type to output */
            redirection_file = &input[i + 1];
        }
        else if (input[i] == '|' && !in_quote)
        {
            input[i] = '\0';  /* Replace pipe symbol with null character */
            redirection_type = 3;  /* Set redirection type to pipe */
        }
        else if (i == 0 || input[i - 1] == '\0')
        {
            args[arg_index] = &input[i];
            arg_index++;
        }

        i++;
    }

    args[arg_index] = NULL;  /* Set the last argument to NULL */

    if (redirection_type == 1)
    {
        freopen(redirection_file, "r", stdin);
    }
    else if (redirection_type == 2)
    {
        freopen(redirection_file, "w", stdout);
    }
    else if (redirection_type == 3)
    {
        fprintf(stderr, "Pipes are not supported in this code snippet.\n");
    }
}

