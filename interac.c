#include "main.h"

/**
 * _interact_mode - denotes if the shell is interactive mode
 * @command_d: structure
 * Return: returns (1) if shell is interactive and (0)
 *  if shell is not interactive
 */

int _interact_mode(cmd_d *command_d)
{
	return (isatty(STDIN_FILENO) && command_d->readfd <= 2);
}
