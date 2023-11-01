#ifndef _MAIN_H_
#define _MAIN_H_

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/**
*typedef void(*sighandler_t)(int)
*sighandler_t signal(int signum, sighandler_t handler);
*int close(int fd);
*int access(const char *pathname, int mode);
*int chdir(const char *path);
*int clisedir(DIR *dirp);
*int execve(cont char *pathname, char *const argv[], char *const envp[]);
*void exit(int status);
*void _exit(int status);
*int fflush(FILE *stream);
*pid_t fork(void);
*void free(void *ptr);
*char *getcwd(char *buf, size_t size);
*ssize_t getline(char **lineptr, size_t *n, FILE *stream);
*pid_t getpid(void);
*int isatty(int fd);
*int kill(pid_t pid, int sig);
*int open(const char *pathname, int flags, mode_t mode);
*DIR *opendir(const char *name);
*void perror(const char *s);
*ssize_t read(int fd, void *buff size_t count);
*struct dirent *readdir(DIR *dirp);
*ssize_t write(int fd,  const void *buf, size_t count);
*pid_t wait3(int wstatus, int option, struct rusage *rusage);
*pid_t wait4(pid_t pid, int *wstatus, int option, struct rusage *rusage);
*pid_t wait(int *wstatus);
*pid_t waitpid(pid_t pid, int *wstatus, int option);
*char *strtok(char *str, const char *delim);
*int stat(const char *pathname, struct stat *statbuf);
*/

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststring - singly linked list
 * @num: the number field
 * @str: a string
 * @nxt: points to the next node
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_s;
/**
 * struct cmd_dat - linked list created
 * @arg: pointer to strings with arguments
 * @argv: pointer to an array of strings
 * @path: string path
 * @argc: argument count (command-line arguments)
 * @line_count: characters count in a string
 * @err_num: error code
 * @linecount_flag: flag to count line of string inputs
 * @fname: pointer to program file
 * @readfd: file descriptor used for reading inputs
 * @env: linked list of environ variables
 * @environ: array of environ variables
 * @env_changed: checks for if environment has changed
 * @history: pointer to past entry
 * @histcount: memory for prev command entered
 * @status: result from prev command
 * @alias: command aliases
 * @cmd_buf: pointer address to command buffer
 * @cmd_buf_type: command buffer (CMD_type: || 0r &&, )
 */
typedef struct cmddata
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_s *env;
	list_s *history;
	list_s *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type; /* accepts ||, &&, ; */
	int readfd;
	int histcount;
} cmd_d;

#define CMDDATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - builtin string function
 * @type: builtin command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(cmd_d *);
} builtin_list;


/* string function(s) */
int the_putchar(char cc);
void append_S(char *str); /*appends strings from character*/
size_t length_string(char *str);
int str_comp(const char *s1, const char *s2);
int replace_str(char **o, char *n);
char *str_concat(char *adr, char *ssrc);
char *str_copy(char *dest, char *src);
char *my_str_dup(const char *str);
char *to_check(const char *haystack, const char *need);


/*fork function(s)*/
void fork_cmd(cmd_d *command_d);

/* simple shell loop functions */
int my_shell(cmd_d *command_d, char **av);
int builtin_find(cmd_d *command_d);
void path_cmd(cmd_d *command_d);

/* parse functions */
int if_exec_cmd(cmd_d *, char *);
char *char_dup(char *, int, int);
char *find_full_path(cmd_d *, char *, char *);


/* error functions */
void append_err_s(char *);
int err_putchar(char);
int fd_putc(char c, int fd);
int fd_puts(char *str, int fd);
int err_atoi(char *s);
void print_err(cmd_d *, char *);
int print_decimal(int entry, int f_d);
char *convert_num(long int no, int base, int _flags);
void rm_comments(char *buff);


/* exit functions */
char *char_string(char *prompt, char s);
char *copy_string(char *dest, char *src, int n); /*Still working on it*/
char *string_concat(char *dest, char *src, int n);

/* free function(s) */
int free_prompt(void **prompt);

/* interactive shell function(s) */
int _interact_mode(cmd_d *command_d);

/* _atoi functions */
int atoi(char *str);
int alpha(int cc);
int delim(char cc, char *dd);

/* alias function(s) */
int set_aliass(cmd_d *command_d, char *str);
int aliass_unset(cmd_d *command_d, char *str);
int to_print_a(list_s *alias_node);
int aliass_command(cmd_d *command_d);

/* token function(s) */
char **tok(char *str, char *delimeter);

/* built in command function */
int command_exit(cmd_d *command_d);
int command_help(cmd_d *command_d);
int command_cd(cmd_d *command_d);
int command_record(cmd_d *command_d)

 
