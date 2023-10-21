#include "main.h"

/**
 * node_add - adds a node to the start of the linked list
 * @h: pointer to head node
 * @str: string field of node
 * @no: node index used by record
 * Return: returns the size of linked list
 */

list_s *node_add(list_s **h, const char *str, int no)
{
	list_s *h_new;

	if (!h)
		return (NULL);
	h_new = malloc(sizeof(list_s));
	if (!h_new)
		return (NULL);
	memory_set((void *)h_new, 0, sizeof(list_s));
	h_new->num = no;
	if (str)
	{
		h_new->str = my_str_dup(str);
		if (!h_new->str)
		{
			free(h_new);
			return (NULL);
		}
	}
	h_new->next = *h;
	*h = h_new;
	return (h_new);
}

/**
 * add_to_list - adds a node to the list
 * @h: pointer to head node
 * @str: string field of node
 * @no: node index used by history
 * Return: returns the size of list
 */

list_s *add_to_list(list_s **h, const char *str, int no)
{
	list_s *new_nd, *node;

	if (!h)
		return (NULL);

	node = *h;
	new_nd = malloc(sizeof(list_s));
	if (!new_nd)
		return (NULL);
	memory_set((void *)new_nd, 0, sizeof(list_s));
	new_nd->num = no;
	if (str)
	{
		new_nd->str = str_duplicate(str);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_nd;
	}
	else
		*h = new_nd;
	return (new_nd);
}

/**
 * print_list_string - prints only the string element of the list
 * @ptr : pointer to the first node
 * Return: returns the size of linked list
 */

size_t print_list_string(const list_s *ptr)
{
	size_t s = 0;

	while (ptr)
	{
		append_S(ptr->str ? ptr->str : "(nil)");
		append_S("\n");
		ptr = ptr->next;
		s++;
	}
	return (s);
}

/**
 * delete_node - deletes node at an index
 * @h: address of pointer to first node
 * @i: index of node to delete
 * Return: returns (1) if deleted and (0) if not
 */

int delete_node(list_s **h, unsigned int i)
{
	list_s *prev, *node;
	unsigned int n = 0;

	if (!h || !*h)
		return (0);

	if (!i)
	{
		node = *h;
		*h = (*h)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (n == i)
		{
			prev->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		n++;
		prev = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees the list
 * @h_ptr: pointer to address of head node
 * Return: returns nothing (void)
 */

void free_list(list_s **h_ptr)
{
	list_s *h, *next, *node;

	if (!h_ptr || !*h_ptr)
		return;
	h = *h_ptr;
	node = h;
	while (node)
	{
		next = node->next;
		free(node->str);
		free(node);
		node = next;
	}
	*h_ptr = NULL;
}
