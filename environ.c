#include "main.h"

/**
 * get_env - a function to provide string array copy
 * @command_d: Struct type
 * Return: the string array copy of the environment
 */

char **get_env(cmd_d *command_d)
{
	if (!command_d->environ || command_d->env_changed)
	{
		command_d->environ = list_to_str(command_d->env);
		command_d->env_changed = 0;
	}
	/*if (strchr(var, ' ') != NULL)
	 {
		 return (NULL);
	 }*/
	 return (command_d->environ);
}


/**
 * setting_env - organise a new environment var,
 * modify an existing one
 * @command_d: Struc type
 * @var: the string environment variable
 * @vv: the string environment variable value
 *  Return: returns (0)
 */

int setting_env(cmd_d *command_d, char *var, char *vv)
{
	char *buffer = NULL, *cc;
	list_s *node;

	if (!var || !vv)
		return (0);

	buffer = malloc(string_length(var) + string_length(vv) + 2);
	if (!buffer)
		return (1);
	if (strchr(var, ' ') != NULL)
	{
		free (buffer);
		return (1);
	}
	my_str_copy(buffer, var);
	str_concat(buffer, "=");
	str_concat(buffer, vv);
	node = command_d->env;
	while (node)
	{
		cc = _check(node->str, var);
		if (cc && *cc == '=')
		{
			free(node->str);
			node->str = buffer;
			command_d->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_to_list(&(command_d->env), buffer, 0);
	free(buffer);
	command_d->env_changed = 1;
	return (0);
}

/**
 * unsetting_env - clears an environment var
 * @command_d: Structure arg
 * @var: the string environment var
 *  Return: when deleted it returns (1), returns (0) otherwise
 */

int unsetting_env(cmd_d *command_d, char *var)
{
	size_t x = 0;
	list_s *node = command_d->env;
	char *prompt;

	if (!var || !node)
		return (0);

	while (node)
	{
		prompt = _check(node->str, var);
		if (prompt && *prompt == '=')
		{
			command_d->env_changed = delete_node(&(command_d->env), x);
			x = 0;
			node = command_d->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (command_d->env_changed);
}
