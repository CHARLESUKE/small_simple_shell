#include "main.h"

/**
 * length_list - this determines length of linked list
 * @prompt: pointer to first or initial node
 * Return: returns the size of linked list
 */
size_t length_list(const list_s *prompt)
{
	size_t s = 0;

	while (prompt)
	{
		prompt = prompt->next;
		s++;
	}
	return (s);
}

/**
 * list_to_str - an array of strings is returned
 * @h: pointer to head node
 * Return: returns an array of strings
 */

char **list_to_str(list_s *h)
{
	list_s *node = h;
	size_t l = length_list(h);
	size_t i;
	char **string;  char *str;

	if (!h || !l)
		return (NULL);
	string = malloc(sizeof(char *) * (l + 1));
	if (!string)
		return (NULL);
	for (l = 0; node; node = node->next, l++)
	{
		str = malloc(length_string(node->str) + 1);
		if (!str)
		{
			for (i = 0; i < l; i++)
				free(string[i]);
			free(string);
			return (NULL);
		}

		str = str_copy(str, node->str);
		string[l] = str;
	}
	string[l] = NULL;
	return (string);
}


/**
 * print_elem - prints all elements of a linked list
 * @h: pointer to head node
 * Return: returns the size of list
 */

size_t print_elem(const list_s *h)
{
	size_t s = 0;

	while (h)
	{
		append_S(convert_num(h->num, 10, 0));
		the_putchar(':');
		the_putchar(' ');
		append_S(h->str ? h->str : "(nil)");
		append_S("\n");
		h = h->next;
		s++;
	}
	return (s);
}

/**
 * node_start - shows the string with prefix
 * @node: pointer to head node
 * @pfix: string to match i.e prefix
 * @cc: the next character after prefix to match
 * Return: returns either a match or nothing
 */

list_s *node_start(list_s *node, char *pfix, char cc)
{
	char *prompt = NULL;

	while (node)
	{
		prompt = to_check(node->str, prefix);
		if (prompt && ((cc == -1) || (*prompt == cc)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_index - obtains the index of a node
 * @h: acts as pointer to node list
 * @n: acts as pointer to the node
 * Return: returns the index of node or -1
 */
ssize_t node_index(list_s *h, list_s *n)
{
	size_t s = 0;

	while (h)
	{
		if (h == n)
			return (s);
		h = h->next;
		s++;
	}
	return (-1);
}
