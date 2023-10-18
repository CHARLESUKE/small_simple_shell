#include "main.h"

/**
 * To search for paths of a file/dir/command
 * This line of codes will do that
 * it basically contains
 * the path to search
 */

char *searching_path(char *command)
{
	char *path = getenv("PATH");
	char *path_dup = strdup(path);
	/* a Copy of the command is created*/
	char entire_path[1024];
	char *dir = strtok(path_dup, ":");

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
			free(path_dup);
			return (strdup(entire_path));
		}


		dir = strtok(NULL, ":"); /* Proceed to the next directory*/
	}

	free(path_dup);

	return (command);
}

