#include "main.h"

/**
 * Change the current working directory to the specified path.
 *
 * @args - is the path to the new directory.
 * @return 0 on success, -1 on failure.
 */

void cd_function(char *args)
{
if (args == NULL)
{
char *home = getenv("HOME");

if (home == NULL)
{
perror("cd: HOME envrionment variable is not set\n");
}
else
{
if (chdir(home) != 0)
{
perror("could not change directory");
}
}
}
else
{
if (chdir(args) != 0)
{
perror("could not change directory");
}
}
}

void exit_function(void)
{

exit(0);

}

