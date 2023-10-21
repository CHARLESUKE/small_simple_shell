#include "main.h"

/**
 * command_exit - exit command for the shell
 * @command_d: structure
 * Return: (1) exits, returns (0) if command_d.argv[0] != "exit".
 */
int command_exit(cmd_d *command_d)
{
	int e_check;

	if (command_d->argv[1])
	{
		e_check = err_atoi(command_d->argv[1]);
		if (e_check == -1)
		{
			command_d->status = 2;
			print_err(command_d, "Incorrect number: ");
			append_err_s(command_d->argv[1]);
			err_putchar('\n');
			return (1);
		}
		command_d->err_num = err_atoi(command_d->argv[1]);
		return (-2);
	}
	command_d->err_num = -1;
	return (-2);
}

/**
 * command_help - gives information on changed directories
 * @command_d: Structure containing arguments
 * Return: returns (0)
 */

int command_help(cmd_d *command_d)
{
	char **arg_arr;

	arg_arr = command_d->argv;
	append_S("Function does not exist \n");
	if (0)
	{
		append_S(*arg_arr);
	}
	return (0);
}


/**
 * command_cd - changes directories
 * @command_d: Structure containing potential arguments
 * Return: returns (0)
 */

int command_cd(cmd_d *command_d)
{
	char *c, *d; /* d stands for directory */
	char buffer[1024];
	int _chdir;

	c = getcwd(buffer, 1024);
	if (!c)
		append_S("TODO: >>fail to getcwd emsg here<<\n");
	if (!command_d->argv[1])
	{
		d = _get_env(command_d, "HOME=");
		if (!d)
			_chdir = chdir((d = _get_env(command_d, "PWD=")) ? d : "/");
		else
			_chdir = chdir(d);
	}
	else if (my_str_comp(command_d->argv[1], "-") == 0)
	{
		if (!_get_env(command_d, "OLDPWD="))
		{
			append_S(c);
			_putchar('\n');
			return (1);
		}
		append_S(_get_env(command_d, "OLDPWD=")), _putchar('\n');
		_chdir = chdir((d = _get_env(command_d, "OLDPWD=")) ? d : "/");
	}
	else
		_chdir = chdir(command_d->argv[1]);
	if (_chdir == -1)
	{
		print_err(command_d, "fail to cd to ");
		append_err_s(command_d->argv[1]), err_putchar('\n');
	}
	else
	{
		set_env(command_d, "OLDPWD", _get_env(command_d, "PWD="));
		set_env(command_d, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * command_record - displays the record list
 * @command_d: Structure
 *  Return: returns (0)
 */
int command_record(cmd_d *command_d)
{
	prints_element(command_d->record);
	return (0);
}
