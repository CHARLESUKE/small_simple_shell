#include "main.h"

/* this is to print the erro message*/
void err_msg(char *command)
{
    char *err_msg;
    char *msg2;

    /* Display the error message*/
    err_msg = "Command '";
    write(STDERR_FILENO, err_msg, strlen(err_msg));
    write(STDERR_FILENO, command, strlen(command));
    msg2 = "' not found\n";
    write(STDERR_FILENO, msg2, strlen(msg2));
    exit(EXIT_FAILURE); /*This goes back to the execve*/

}
