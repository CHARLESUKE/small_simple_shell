#include "main.h"

/**
 * searching_path - This function gets the path of commands
 * @command: The name of the command to search for in the PATH.
 * Return: The result of the function.
 */

char *searching_path(char *command)
{
	char *path = getenv("PATH");
	char *path_dup = strdup(path);
	/* a Copy of the command is created*/
	char entire_path[1024];
	char *dir = strtok(path_dup, ":");

	char *result = NULL;

	/* We create a while loop below to iterate and concatenate*/
	while (dir != NULL)
	{
		/* a copy of the directory is created using strcpy*/
		strcpy(entire_path, dir);
		if (entire_path[strlen(entire_path) - 1] != '/')
		{
			strcat(entire_path, "/");
		}

		/* we then Concatenate the path with the command*/
		strcat(entire_path, command);

		/* using access function, we check to see if the file exists */
		if (access(entire_path, F_OK) == 0 && access(entire_path, X_OK) == 0)
		{
			result = strdup(entire_path); /* Store the result in 'result'.*/
			break; /* Exit the loop when the command is found.*/
		}


		dir = strtok(NULL, ":"); /* Proceed to the next directory*/
	}

	free(path_dup);

	if (result == NULL) /* If 'result' is still NULL, the command was not found.*/
	{
		result = strdup(command); /* Return a copy of 'command'. */
	}

	return (result);
}

