#include "main.h"

/**
 * fork_cmd - forks a an exec to run command
 * @command_d: the parameter to pass
 * Return: nothing
 */
void fork_cmd(cmd_d *command_d)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error input:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(command_d->path, command_d->argv, get_env(command_d)) == -1)
		{
			command_free(command_d, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(command_d->status));
		if (WIFEXITED(command_d->status))
		{
			command_d->status = WEXITSTATUS(command_d->status);
			if (command_d->status == 126)
				print_err(command_d, "Permission denied\n");
		}
	}
}
