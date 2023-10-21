#include "main.h"

/**
 * record_file - gets the record or history file
 * @command_d: structure type
 * Return: returns record file
 */

char *record_file(cmd_d *command_d)
{
	char *buffer, *_dir;

	_dir = _get_env(command_d, "HOME=");
	if (!_dir)
		return (NULL);
	buffer = malloc((string_length(_dir) + string_length(HIST_FILE) + 2) *
			sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	my_str_copy(buffer, _dir);
	str_concat(buffer, "/");
	str_concat(buffer, HIST_FILE);
	return (buffer);
}



/**
 * rd_record - reads record from file
 * @command_d: structure type
 * Return: returns record_count if successful and (0) if not
 */

int rd_record(cmd_d *command_d)
{
	int a, l = 0, line_count = 0;
	ssize_t f_desc, read_len, f_size = 0;
	struct stat st;
	char *buffer = NULL, *file_name = record_file(command_d);

	if (!file_name)
		return (0);

	f_desc = open(file_name, O_RDONLY);
	free(file_name);
	if (f_desc == -1)
		return (0);
	if (!fstat(f_desc, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (f_size + 1));
	if (!buffer)
		return (0);
	read_len = read(f_desc, buffer, f_size);
	buffer[f_size] = 0;
	if (read_len <= 0)
		return (free(buffer), 0);
	close(f_desc);
	for (a = 0; a < f_size; a++)
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			build_record(command_d, buf + l, line_count++);
			l = a + 1;
		}
	if (l != a)
		build_record(command_d, buffer + l, line_count++);
	free(buffer);
	command_d->reccount = line_count;
	while (command_d->reccount-- >= HIST_MAX)
		delete_node(&(command_d->record), 0);
	num_record(command_d);
	return (command_d->reccount);
}

/**
 * write_record - creates a new file, or makes changes to an existing file
 * @command_d: struct type
 * Return: returns (1) if successful and (-1) if not
 */
int write_record(cmd_d *command_d)
{
	char *f_name = record_file(command_d);
	ssize_t f_desc;
	list_s *node = NULL;

	if (!f_name)
		return (-1);

	f_desc = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);
	if (f_desc == -1)
		return (-1);
	for (node = command_d->record; node; node = node->next)
	{
		fd_puts(node->str, f_desc);
		fd_putc('\n', f_desc);
	}
	fd_putc(BUF_FLUSH, f_desc);
	close(f_desc);
	return (1);
}


/**
 * build_record - adds to the record linked list
 * @command_d: Struct arguments
 * @buffer: buffer
 * @line_count: the record count
 * Return: returns (0)
 */

int build_record(cmd_d *command_d, char *buffer, int line_count)
{
	list_s *n = NULL;

	if (command_d->record)
		n = command_d->record;
	add_to_list(&n, buffer, line_count);

	if (!command_d->record)
		command_d->record = n;
	return (0);
}

/**
 * num_record - numbers the record list after update
 * @command_d: Struct arguments
 * Return: returns the new record count
 */

int num_record(cmd_d *command_d)
{
	list_s *nd = command_d->record;
	int x = 0;

	while (nd)
	{
		nd->num = x++;
		nd = nd->next;
	}
	return (command_d->reccount = x);
}
