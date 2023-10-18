#include "main.h"


/*to print environment to standard output*/

void get_env(char **environ)
{
        size_t start = 0;

        while (environ[start])
        {
                write(STDOUT_FILENO, environ[start], strlen(environ[start]));
                write(STDOUT_FILENO, "\n", 1);
                start++;
        }
}

