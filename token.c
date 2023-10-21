#include "main.h"

/**
 * **tok - token which splits a string into words and repeated
 * delimeter are ignored
 * @str: string input
 * @delimeter: delimeter
 * Return: returns the address to a string array
 */

char **tok(char *str, char *delimeter)
{
	int a, b, i, j;
	int word_num = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!delim(str[a], delimeter) && (delim(str[a + 1], delimeter)
					|| !str[a + 1]))
			word_num++;

	if (word_num == 0)
		return (NULL);
	s = malloc((1 + word_num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < word_num; b++)
	{
		while (delim(str[a], delimeter))
			a++;
		i = 0;
		while (!delim(str[a + i], delimeter) && str[a + i])
			i++;
		s[b] = malloc((i + 1) * sizeof(char));
		if (!s[b])
		{
			for (i = 0; i < b; i++)
				free(s[i]);
			free(s);
			return (NULL);
		}
		for (j = 0; j < i; j++)
			s[b][j] = str[a++];
		s[b][j] = 0;
	}
	s[b] = NULL;
	return (s);
}
