#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

char *searching_path(char *command);
extern char **environ;

/* For builtin*/
void cd_function(char *args);
void exit_function(void);
void err_msg(char *command);
void get_env(char **environ);
void handle_signal(int signal);

#endif

