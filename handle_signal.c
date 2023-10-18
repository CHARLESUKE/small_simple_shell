#include "main.h"

/*this line of codes is for handling signal, ctrl + c*/

void handle_signal(int signal)
{
    char *prmpt = "\nprompt$ ";

    (void)signal;
    write(1, prmpt, strlen(prmpt));

    fflush(stdout);
}

