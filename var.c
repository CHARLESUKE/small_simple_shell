#include "main.h"

/**
 * chain_is - test for a chain delimeter
 * @command_d: parameter struct
 * @buff: the character buffer
 * @ptr: pointer to the current position in buf
 * Return: returns (1) if true
 */

int chain_is(cmd_d *command_d, char *buffer, size_t *prompt)
{
	size_t a = *prompt;

	if (buffer[a] == '|' && buffer[a + 1] == '|')
	{
		buffer[a] = 0;
		a++;
		command_d->cmd_buf_type = CMD_OR;
	}
	else if (buffer[a] == '&' && buffer[a + 1] == '&')
	{
		buffer[a] = 0;
		a++;
		command_d->cmd_buf_type = CMD_AND;
	}
	else if (buffer[a] == ';')
	{
		buffer[a] = 0;
		command_d->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*prompt = a;
	return (1);
}

/**
 * chain_check - checks for continue chaining
 * @command_d: the  structure type
 * @buffer: the char buffer
 * @adr: current position address in buffer
 * @s: starting position
 * @len: buffer's length
 * Return: returns nothing (void)
 */

void chain_check(cmd_d *command_d char *buffer, size_t *adr, size_t s, size_t len)
{
	size_t p = *adr;

	if (command_d->cmd_buf_type == CMD_AND)
	{
		if (command_d->status)
		{
			buffer[s] = 0;
			p = len;
		}
	}
	if (command_d->cmd_buf_type == CMD_OR)
	{
		if (!command_d->status)
		{
			buffer[s] = 0;
			p = len;
		}
	}

	*adr = p;
}

/**
 * replace_alias - replaces an aliases in the token strings
 * @command_d: the struct type
 * Return: returns (1) if alias is replaced, and (0) if not
 */

int alias_replace(cmd_d * command_d)
{
	int i;
	list_s *node;
	char *cc;

	for (i = 0; i < 10; i++)
	{
		node = start_node(command_d->alias, command_d->argv[0], '=');
		if (!node)
			return (0);
		free(command_d->argv[0]);
		cc = char_string(node->str, '=');
		if (!c)
			return (0);
		c = str_duplicate(c + 1);
		if (!c)
			return (0);
		command_d->argv[0] = c;
	}
	return (1);
}

/**
 * replace_var - replaces var
 * @command_d: struct parameter
 * Return: returns (1) if replaced and (0) if not
 */

int replace_var(cmd_d *command_d)
{
	int a = 0;
	list_s *node;

	for (a = 0; command_d->argv[a]; a++)
	{
		if (command_d->argv[a][0] != '$' || !command_d->argv[a][1])
			continue;

		if (!my_str_comp(command_d->argv[a], "$?"))
		{
			replace_str(&(command_d->argv[a]),
					str_duplicate(convert_num(cmd_dat->status, 10, 0)));
			continue;
		}
		if (!my_str_comp(command_d->argv[a], "$$"))
		{
			replace_str(&(command_d->argv[a]),
					str_duplicate(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = start_node(command_d->env, &command_d->argv[a][1], '=');
		if (node)
		{
			replace_str(&(command_d->argv[a]),
					str_duplicate(char_string(node->str, '=') + 1));
			continue;
		}
		replace_str(&command_d->argv[a], str_duplicate(""));

	}
	return (0);
}
