#include "main.h"

/**
 **char_string - checks for a character in a string
 *@s: the string to look for
 *@prompt: pointer
 *Return: return (s) a pointer to the memory area s
 */
char *char_string(char *prompt, char s)
{
	do {
		if (*prompt == s)
			return (prompt);
	} while (*prompt++ != '\0');

	return (NULL);
}

/**
 **copy_string - copies a string
 *@dest: string estination
 *@src: string source
 *@n: characters amount copied
 *Return: returns the concatenated string
 */
char *copy_string(char *dest, char *src, int n)
{
	int a, b;
	char *d = dest; /* Destination */

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (d);
}

/**
 **string_concat - concatenates two strings
 *@dest: the first string input
 *@src: the second string input
 *@n: the amount of bytes to be used
 *Return: returns the concatenated string
 */

char *string_concat(char *dest, char *src, int n)
{
	int a, b;
	char *d = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[b] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (d);
}
