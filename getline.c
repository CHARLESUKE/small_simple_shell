#include "main.h"

/**
 * to_getline - this reads an entire line from stream from STDIN,
 * a created (getline) function
 * @command_d: struct parameter
 * @prompt: address to the pointer to buffer
 * @len: preallocated prompt buffer size
 * Return: size of preallocated size
 */
int to_getline(cmd_d *command_d, char **prompt, size_t *len)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, l;
	char *p = NULL, *prompt_dup = NULL;
	char *c;
	size_t j;
	ssize_t k = 0, s = 0;

	p = *prompt;
	if (p && len)
		s = *len;
	if (i == l)
		i = l = 0;

	k = buf_read(command_d, buffer, &l);
	if (k == -1 || (k == 0 && l == 0))
		return (-1);

	c = string_char(buf + i, '\n');
	j = c ? 1 + (unsigned int)(c - buffer) : l;
	prompt_dup = my_realloc(p, s, s ? s + j : j + 1);
	if (!prompt_dup) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		string_concat(prompt_dup, buffer + i, j - i);
	else
		string_copy(prompt_dup, buffer + i, j - i + 1);

	s += j - i;
	i = j;
	p = prompt_dup;

	if (len)
		*len = s;
	*prompt = p;
	return (s);
}


/**
 * buffer_input - buffers chained commands
 * @command_d: structure type
 * @buffer:  pointer to the buffer
 * @len: address of length variable
 * Return: bytes read
 */
ssize_t buffer_input(cmd_d *command_d, char **buffer, size_t *len)
{
	ssize_t s = 0;  size_t len_t = 0;

	if (!*len) /* if empty, fill it */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_signal);
#if USE_GETLINE
		s = getline(buf, &len_t, stdin);
#else
		s = to_getline(command_d, buffer, &len_t);
#endif
		if (s > 0)
		{
			if ((*buffer)[s - 1] == '\n')
			{
				(*buffer)[s - 1] = '\0';
				s--;
			}
			command_d->linecount_flag = 1;
			rm_comments(*buffer);
			build_history(command_d, *buffer, command_d->histcount++);
			{
				*len = s;
				command_d->cmd_buf = buffer;
			}
		}
	}
	return (s);
}

/**
 * _input - gets a line minus the newline
 * @command_d: structure type
 * Return: number of bytes read
 */

ssize_t _input(cmd_d *command_d)
{
	static size_t l; static size_t i, j;
	ssize_t s = 0;
	char **buffer_prompt = &(command_d->arg), *p;
	static char *buffer;

	_putchar(BUF_FLUSH);
	s = buffer_input(command_d, &buffer, &l);
	if (s == -1) /* End of file */
		return (-1);
	if (l)
	{
		j = i; /* itertor */
		p = buffer + i;

		chain_check(command_d, buffer, &j, i, l);
		while (j < l) /* iterate till a semicolon or end */
		{
			if (is_Chain(command_d, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= l)
		{
			i = l = 0; /* reset position and length */
			command_d->cmd_buf_type = CMD_NORM;
		}

		*buffer_prompt = p;
		return (string_length(p));
	}

	*buffer_prompt = buffer;
	return (s); /* return length */
}

/**
 * read_buffer - reads an input buffer
 * @command_d: structure type
 * @buffer: buffer
 * @s: size of buffer
 * Return: (i)
 */
ssize_t read_buffer(cmd_d *command_d, char *buf, size_t *s)
{
	ssize_t i = 0;

	if (*s)
		return (0);
	i = read(command_d->readfd, buffer, READ_BUF_SIZE);
	if (i >= 0)
		*s = i;
	return (i);
}


/**
 * handle_signal - blocks ctrl-C from exiting and display
 * a new prompt
 * @sig_num: signal number
 * Return: returns nothing (void)
 */

void handle_signal(__attribute__((unused))int sig_num)
{
	append_S("\n");
	append_S("$ ");
	_putchar(BUF_FLUSH);
}
