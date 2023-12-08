#include "shell.h"

/**
 * initializer - starts executing everything
 * @current_command: array of command arguments
 * @type_command: type of command (EXTERNAL_COMMAND, PATH_COMMAND, etc.)
 *
 * Return: void
 */
void initializer(char **current_command, int type_command)
{
    pid_t PID;

    /* Check if the command is an external command or a command with a path */
    if (type_command == EXTERNAL_COMMAND || type_command == PATH_COMMAND)
    {
        /* Create a child process to execute the command */
        PID = fork();

        if (PID == 0) /* Child process */
        {
            execute_command(current_command, type_command);
        }
        else /* Parent process */
        {
            waitpid(PID, &status, 0);
            status >>= 8; /* Get the exit status of the child process */
        }
    }
    else
    {
        /* Execute the command directly (internal command) */
        execute_command(current_command, type_command);
    }
}

