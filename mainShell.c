#include "shell.h"

char **commands = NULL;
char *line = NULL;
char *shell_name = NULL;
int status = 0;

/**
 * main - the main shell code
 * @argc: number of arguments passed
 * @argv: program arguments to be parsed
 *
 * Applies the functions in utils and helpers,
 * implements EOF, prints error on failure.
 *
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv)
{
    char **current_command = NULL;
    int i, type_command = 0;
    size_t n = 0;

    /* Register the ctrl_c_handler function for handling SIGINT signals */
    signal(SIGINT, ctrl_c_handler);

    /* Set the shell_name to the program name */
    shell_name = argv[0];

    while (1)
    {
        non_interactive(); /* Handle non-interactive mode */

        /* Display shell prompt */
        print(" ($) ", STDOUT_FILENO);

        /* Read input line from the user */
        if (getline(&line, &n, stdin) == -1)
        {
            free(line);
            exit(status);
        }

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

            /* Initialize and execute the command */
            initializer(current_command, type_command);

            free(current_command); /* Free the memory allocated for current_command */
        }

        free(commands); /* Free the memory allocated for commands */
    }

    free(line); /* Free the memory allocated for the input line */
    return (status);
}

