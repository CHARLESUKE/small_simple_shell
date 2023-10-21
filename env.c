#include "main.h"

/**
 * _get_env - gets the value of an environment var
 * @command_d: Struct  arg
 * @name: environment variable name
 * Return: the value of environment
 */

char *_get_env(cmd_d *command_d, const char *name)
{
	list_s *n = command_d->env;
	char *a;

	while (n)
	{
		a = _check(n->str, name);
		if (a && *a)
			return (a);
		n = n->next;
	}
	return (NULL);
}

/**
 * real_env - this prints the current environment
 * @command_d: Struct type
 * Return: returns(0)
 */

int real_env(cmd_d *command_d)
{
	print_list_string(command_d->env);
	return (0);
}

/**
 * setting_environ - organises a new environment variable,
 * and modify an existing one
 * @command_d: Struct type.
 *  Return: returns (0)
 */

int setting_environ(cmd_d *command_d)
{
	if (command_d->argc != 3)
	{
		append_err_s("Arguments are not complete\n");
		return (1);
	}
	if (setting_env(command_d, command_d->argv[1], command_d->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetting_environ - clears an environment variable
 * @command_d: Structure arguments
 * Return: return (0)
 */

int unsetting_environ(cmd_d *command_d)
{
	int a;

	if (command_d->argc == 1)
	{
		append_err_s("too few arguments.\n");
		return (1);
	}
	for (a = 1; a <= command_d->argc; a++)
		unset_env(command_d, command_d->argv[a]);

	return (0);
}

/**
 * pop_env - makes a cluster of environment linked list
 * @command_d: Struct type
 * Return: returns environment list
 */

int pop_env(cmd_d *command_d)
{
	list_s *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node(&node, environ[a], 0);
	command_d->env = node;
	return (0);
}
