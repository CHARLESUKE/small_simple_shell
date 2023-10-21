#include "main.h"

/**
 * my_shell - this is the loop of main shell
 * @command_d: parameter
 * @av: arg vector
 * Return: returns (0) if successful, and (1) if there's an error
 * or an error message
 */

int my_shell(cmd_d *command_d, char **av)
{
	ssize_t a = 0;
	int _built = 0;

	while (a != -1 && _built != -2)
	{
		clear_cmd(command_d);
		if (interactive_shell(command_d))
			append_S("$ ");
		err_putchar(BUF_FLUSH);
		a = _input(command_d);
		if (a != -1)
		{
			set_command(command_d, av);
			_built = find_builtIn(command_d);
			if (_built == -1)
				path_cmd(command_d);
		}
		else if (interactive_shell(command_d))
			the_putchar('\n');
		command_free(command_d, 0);
	}
	write_record(command_d);
	command_free(command_d, 1);
	if (!_interact_mode(command_d) && command_d->status)
		exit(command_d->status);
	if (_built == -2)
	{
		if (command_d->err_num == -1)
			exit(cmd_dat->status);
		exit(cmd_dat->err_num);
	}
	return (_built);
}

/**
 * builtin_find - checks for built in command
 * @command_d: parameter
 * Return: returns (-1) if builtin command not found, (0) if builtin
 * command is executed successfully
 * and (1) if found but not executed successfully
 */
int builtin_find(cmd_d *command_d)
{
	int a, ret_builtin = -1;
	builtin_list bl[] = {
		{"exit", command_exit},
		{"env", my_env},
		{"help", help_cmd},
		{"history", history_cmd},
		{"setenv", setting_environ},
		{"unsetenv", unsetting_environ},
		{"cd", cd_cmd},
		{"alias", alias_cmd},
		{NULL, NULL}
	};

	for (a = 0; bl[a].type; a++)
		if (my_str_comp(cmd_dat->argv[0], bl[a].type) == 0)
		{
			cmd_dat->line_count++;
			ret_builtin = bl[a].func(cmd_dat);
			break;
		}
	return (ret_builtin);
}

/**
 * path_cmd - checks for a command in PATH
 * @command_d: the parameter & returnstruct
 *
 * Return: void
 */
void path_cmd(cmd_d *command_d)
{
	char *_path = NULL;
	int i, j;

	command_d->path = command_d ->argv[0];
	if (command_d->linecount_flag == 1)
	{
		command_d->line_count++;
		command_d->linecount_flag = 0;
	}
	for (i = 0, j = 0; command_d->arg[i]; i++)
		if (!delim(command_d->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	_path = find_full_path(command_d, _get_env(command_d, "PATH="), command_d->argv[0]);
	if (_path)
	{
		command_d->path = _path;
		fork_cmd(command_d);
	}
	else
	{
		if ((_interact_mode(command_d) || _get_env(command_d, "PATH=")
					|| command_d->argv[0][0] == '/') && if_exec_cmd(command_d, command_d->argv[0]))
			fork_cmd(command_d);
		else if (*(command_d->arg) != '\n')
		{
			command_d->status = 127;
			print_err(command_d, "file not found\n");
		}
	}
}
