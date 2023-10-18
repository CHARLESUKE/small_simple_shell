#include "main.h"


/**
 * get_env - exit shell with a specific status
 * @environ: The exit status to set
 * Return: exit value
 */

void get_env(char **environ)
{
	size_t start = 0;

	while (environ[start])
	{
		write(STDOUT_FILENO, environ[start], strlen(environ[start]));
		write(STDOUT_FILENO, "\n", 1);
		start++;
	}
}

