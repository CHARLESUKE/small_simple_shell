#include "main.h"

/**
 * handle_signal - exit shell with a specific status
 * @signal: to handle signal like when ctrl + c is passed
 * Return: o on success, 1 on failure
 */

void handle_signal(int signal)
{
	char *prmpt = "\nprompt$ ";

	(void)signal;
	write(1, prmpt, strlen(prmpt));

	fflush(stdout);
}

