#include "main.h"


/**
 * the_putchar - it writes the character c to standard outpt
 * @cc: The character to print
 * Return: Successful (0)
 * On error, -1 is returned, and errno is set appropriately
 */
int the_putchar(char cc)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (cc == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (cc != BUF_FLUSH)
		buffer[i++] = cc;
	return (1);
}



/**
 * append_S - prints a string
 * @str: pointer to string
 */
void append_S(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}


/**
 * *str_copy - it copies a string
 * @str: first string input
 * @src: second string input
 * Return: returns the result of the comparison
 */
char *str_copy(char *dest, char *src)
{
	int s = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[s])
	{
		dest[s] = src[s];
		s++;
	}
	dest[s] = 0;
	return (dest);
}

/**
 * my_str_dup - duplicates a string input or output
 * @str: the string input
 * Return: returns the address to the string duplicated
 */
char *my_str_dup(const char *str)
{
	char *dup;
	int len = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	for (len++; len--;)
		dup[len] = *--str;
	return (dup);
}
	
/**
 * replace_str - it replaces string
 * @o:acts as pointer to addres of previous string
 * @n: the new string
 * Return: returns (1) if replaced and (0) if not
 */

int replace_str(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
