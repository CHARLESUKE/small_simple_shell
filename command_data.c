#include "main.h"

/**
 * set_command - initialize command structure
 * @command_d: struct type
 * @av: argument vector
 */

void set_command(cmd_d * command_d, char **av)
{
	int a = 0;

	command_d->fname = av[0];
	if (command_d->arg)
	{
		command_d->argv = token(command_d->arg, " \t");
		if (!command_d->argv)
		{
			command_d->argv = malloc(2 * sizeof(char *));
			if (command_d->argv)
			{
				command_d->argv[0] = str_duplicate(command_d->arg);
				command_d->argv[1] = NULL;
			}
		}
		for (a = 0; command_d->argv && command_d->argv[a]; a++)
			;
		command_d->argc = a;

		replace_alias(command_d);
		var_replace(command_d);
	}
}

/**
 * clear_command - initialize command structure
 * @command_d: structure type
 */

void clear_command(cmd_d *command_d)
{
	command_d->arg = NULL;
	command_d->argv = NULL;
	command_d->path = NULL;
	command_d->argc = 0;
}

/**
 * command_free - frees command
 * @command_d: structure type
 * @t: returns (Nothing) and true if action is successful
 */

void command_free(cmd_d *command_d, int t)
{
	str_free(command_d->argv);
	command_d->argv = NULL;
	command_d->path = NULL;
	if (t)
	{
		if (!command_d->cmd_buf)
			free(command_d->arg);
		if (command_d->env)
			free_list(&(command_d->env));
		if (command_d->record)
			free_list(&(command_d->record));
		if (command_d->alias)
			free_list(&(command_d->alias));
		str_free(command_d->environ);
			command_d->environ = NULL;
		_free_ptr((void **)command_d->cmd_buf);
		if (command_d->readfd > 2)
			close(command_d->readfd);
		_putchar(BUF_FLUSH);
		}
}
