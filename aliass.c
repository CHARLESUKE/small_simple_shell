#include "main.h"

/**
 * set_aliass - sets aliass to accept string input
 * @command_d: strucyture type
 * @str: the string aliass
 * Return: always return (0) if successful and (1) if
 * there's an error
 */

int set_aliass(cmd_d *command_d, char *str)
{
	char *prompt;

	prompt = string_char(str, '=');
	if (!prompt)
		return (1);
	if (!*++prompt)
		return (aliass_unset(command_d, str));

	aliass_unset(command_d, str);
	return (add_to_list(&(command_d->alias), str, 0) == NULL);
}

/**
 * aliass_unset - removes alisas command
 * @command_t: structure type
 * @str: the string alias
 * Return: returns (0) if successful and (1) if unsuccessful
 */
int aliass_unset(cmd_d *command_d, char *str)
{
	char *prompt;
	char a;
	int res;

	prompt = string_char(str, '=');
	if (!prompt)
		return (1);
	a = *prompt;
	*prompt = 0;
	res = delete_node(&(command_d->alias),
		node_index(command_d->alias, start_node(command_d->alias, str, -1)));
	*prompt = a;
	return (res);
}


/**
 * to_print_a- function toprints an alias string
 * @_node: the alias node
 * Return: returns (0) if successful and (1) if not
 */
int to_print_a(list_s *alias_node)
{
	char *prompt = NULL;
	char *a = NULL;

	if (alias_node)
	{
		prompt = string_char(alias_node->str, '=');
		for (a = alias_node->str; a <= prompt; a++)
			_putchar(*a);
		_putchar('\'');
		append_S(prompt + 1);
		append_S("'\n");
		return (0);
	}
	return (1);
}

/**
 * aliass_command - mimics the alias command
 * @command_d: Structure type
 *  Return: returns (0)
 */
int aliass_command(cmd_d *command_d)
{
	int a = 0;
	char *prompt = NULL;
	list_s *node = NULL;

	if (command_d->argc == 1)
	{
		node = command_d->alias;
		while (node)
		{
			to_print_a(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; command_d->argv[a]; a++)
	{
		prompt = string_char(command_d->argv[a], '=');
		if (prompt)
			set_aliass(command_d, command_d->argv[a]);
		else
			to_print_a(start_node(command_d->alias, command_d->argv[a], '='));
	}

	return (0);
