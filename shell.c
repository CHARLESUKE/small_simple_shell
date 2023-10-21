#include "main.h"

/**
 * main - entry point for simple shell
 * @ac: argument count
 * @av: argument vector
 * Return: returns (0) if successful, and (1) if there
 * is an error
 */

int main(int ac, char **av)
{
	cmd_d cmddat[] = { CMDDATA_INIT };
	int file_desc = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_desc)
			: "r" (file_desc));

	if (ac == 2)
	{
		file_desc = open(av[1], O_RDONLY);
		if (file_desc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				append_error_s(av[0]);
				append_error_s(": 0: Can't open ");
				append_error_s(av[1]);
				err_putchar('\n');
				err_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		cmddat->readfd = file_desc;
	}
	pop_env(cmddat);
	rd_record(cmddat);
	shell(cmddat, av);
	return (EXIT_SUCCESS);
}
