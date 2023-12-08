#include "shell.h"

/**
 * env - prints the current environment
 * @tokenized_command: command entered (unused)
 *
 * Return: void
 */
void env(char **tokenized_command __attribute__((unused)))
{
    int i;

    for (i = 0; environ[i] != NULL; i++)
    {
        print(environ[i], STDOUT_FILENO);
        print("\n", STDOUT_FILENO);
    }
}

/**
 * quit - exits the shell
 * @tokenized_command: command entered
 *
 * Return: void
 */
void quit(char **tokenized_command)
{
    int num_token = 0, arg;

    /* Count the number of tokens in the command */
    for (; tokenized_command[num_token] != NULL; num_token++)
        ;

    if (num_token == 1)
    {
        /* Clean up and exit the shell */
        free(tokenized_command);
        free(line);
        free(commands);
        exit(status);
    }
    else if (num_token == 2)
    {
        /* If there's one argument, try to exit with that status */
        arg = _atoi(tokenized_command[1]);
        if (arg == -1)
        {
            /* Print an error message for an illegal number */
            print(shell_name, STDERR_FILENO);
            print(": 1: exit: Illegal number: ", STDERR_FILENO);
            print(tokenized_command[1], STDERR_FILENO);
            print("\n", STDERR_FILENO);
            status = 2; /* Set status to indicate an error */
        }
        else
        {
            /* Clean up and exit the shell with the specified status */
            free(line);
            free(tokenized_command);
            free(commands);
            exit(arg);
        }
    }
    else
    {
        /* Print an error message for too many arguments */
        print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
    }
}

