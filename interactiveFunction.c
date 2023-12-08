#include "shell.h"

/**
 * non_interactive - handles non-interactive mode
 *
 * Return: void
 */
void non_interactive(void)
{
    char **current_command = NULL;
    int i, type_command = 0;
    size_t n = 0;

    /* Check if stdin is not a terminal (non-interactive mode) */
    if (!(isatty(STDIN_FILENO)))
    {
        /* Read input lines until EOF */
        while (getline(&line, &n, stdin) != -1)
        {
            remove_newline(line); /* Remove newline characters */
            remove_comment(line); /* Remove comments from the line */
            commands = tokenizer(line, ";"); /* Tokenize the line by semicolons */

            /* Loop through each command separated by semicolons */
            for (i = 0; commands[i] != NULL; i++)
            {
                current_command = tokenizer(commands[i], " "); /* Tokenize each command by spaces */

                /* Check if the first token is NULL (empty command) */
                if (current_command[0] == NULL)
                {
                    free(current_command);
                    break;
                }

                type_command = parse_command(current_command[0]); /* Determine the type of command */
                initializer(current_command, type_command); /* Initialize and execute the command */
                free(current_command); /* Free the memory allocated for current_command */
            }

            free(commands); /* Free the memory allocated for commands */
        }

        free(line); /* Free the memory allocated for the input line */
        exit(status); /* Exit the shell with the final status */
    }
}

