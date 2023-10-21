#include "main.h"

/**
 * append_error_s- prints an input string
 * @s: the error string to be printed
 * Return: returns nothing (void)
 */
void append_error_s(char *s)
{
	int a = 0;

	if (!s || s == NULL)
		return;
	while (s[a] != '\0')
	{
		err_putchar(s[a]);
		a++;
	}
}

/**
 * error_putchar - writes the character c to stderr
 * @c: The character to print
 * Return: If successful (1) while if an error occurs,
 * (-1) is returned, and errno is set appropriately
 */

int error_putchar(char c)
{
	static int a;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buffer, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buffer[a++] = c;
	return (1);
}

/**
 * _putc_fd - writes the character to given file
 * @cc: The printed character
 * @fd: The filedescriptor to write to
 * Return: If successful (1), if there is an error (-1) is returned,
 * and errno is set appropriately
 */

int _putc_fd(char cc, int f_d)
{
	static int a;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, a);
		a = 0;
	}
	if (cc != BUF_FLUSH)
		buffer[a++] = cc;
	return (1);
}

/**
 * _puts_fd - prints an input string in the fd
 * @s: the string to be printed
 * @fd: the file descriptor to write to
 * Return: returns the character inputted
 */
int _puts_fd(char *s, int fd)
{
	int a = 0;

	if (!s)
		return (0);
	while (*s)
	{
		a += _putc_fd(*s++, fd);
	}
	return (a);
}
