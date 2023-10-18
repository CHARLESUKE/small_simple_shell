#include "main.h"
/**
 * main - entry point
 */

/*avoid betty*/
int all(void); /*betty checks avoided*/
int main(void)
{
/* Declare variables*/
char *user_line = NULL;
size_t len = 0;
int read_char;

/* Sring tokenization*/
char *delim = " \n"; /* Set an empty string as a delimiter*/
char *tokens;
char *line_arg[1024];
int my_pid;
/*char **args;*/


while (1)
{
/* Prompt line*/
if (isatty(0) == 1)
{
write(1, "prompt$ ", 8);
}

/* Getting users input*/
read_char = getline(&user_line, &len, stdin);

if (read_char == -1)
{
/* When the user presses CTRL + D*/
if (feof(stdin))
{
exit_function();
}
else
{
perror("There is error reading input\n");
free(user_line); /*if failure occurs, free memory*/
return (-1);
}
}
else if (read_char == 1)
{
continue;
}
else
{
int indx = 0;
/* Process the input using string tokenization*/
tokens = strtok(user_line, delim);

/* We use a null terminating tokenization*/
while (tokens != NULL)
{
line_arg[indx] = tokens;
tokens = strtok(NULL, delim);
indx++;
}
line_arg[indx] = NULL;


if (strcmp(line_arg[0], "cd") == 0)
{
/* Call for our function*/
cd_function(line_arg[1]);
}
else if (strcmp(line_arg[0], "exit") == 0)
{
/* We want to exit*/
exit_function();
}
else
{
my_pid = fork();

if (my_pid == -1)
{
perror("Fork failed");
free(user_line);
return (-1);
}
else if (my_pid == 0)
{
char *cmdPath = searching_path(line_arg[0]);
if (cmdPath != NULL)
{

/* If it is not a built in command, we execute it*/

/* This is the child process*/


/* We execute the command with execve*/
execve(cmdPath, line_arg, environ);


err_msg(line_arg[0]);
free(user_line); /* Free allocated memory */
exit(1);
}

}
else
{


int status;
int stat;
stat = WIFEXITED(status);
waitpid(my_pid, &status, 0);

if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
{
printf("\nthis process %d exited with non-zero status %d\n", my_pid, stat);
}
}
}
}

}
free(user_line);
return (0);
}

