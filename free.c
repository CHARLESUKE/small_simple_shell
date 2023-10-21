#include "main.h"

/**
 * free_prompt - frees the pointer address
 * @prompt: pointer address
 * Return: returns (0) if action fails else returns (1)
 */
int free_prompt(void **prompt)
{
	if (prompt && *prompt)
	{
		free(*prompt);
		*prompt = NULL;
		return (1);
	}
	return (0);
}
