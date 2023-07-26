#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


/* Used for buffers used in reading and writing operations */

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Used for linking multiple commands together */

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Used for the conversion of numbers */

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


/* Equals 1 when utilizing the system's getline() function */

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - Definition of a singly linked list structure
 * @num: The of number field
 * @str: A string field
 * @next: points to the next node in the list
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Definition of a structure that contains pseudo-arguments
 * to pass into a function,allowing a uniform prototype
 * for a function pointer structure.
 * @arg: A string generated from the getline function containing arguements
 * @argv: An array of strings generated from the string 'arg
 * @path: a string that rep path for the current command
 * @argc: An integer that represents the count of command-line argument count
 * @line_count: An integer that represents the error count
 * @err_num: An integer that represents the error code used for exit() calls.
 * @linecount_flag:  A flag indicating whether to count current line of input
 * @fname: A string that represents the filename of the program.
 * @env: A linked list that serves as a local copy of the environ variable.
 * @environ: A custom modified copy of the environ variable
 * @history: The history node used for tracking command history.
 * @alias: The alias node used for managing command aliases.
 * @env_changed: A flag indicating whether environ variable has been changed
 * @status: The return status of the last executed command.
 * @cmd_buf: The address of a pointer to cmd_buf, used for chaining commands
 * @cmd_buf_type: The type command chaining (CMD_type) such as ||, &&, or ;.
 * @readfd: The file descriptor used for reading line input
 * @histcount: The count of history line numbers.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* Pointer>cmd buffer>in mem management> ';' chain */
	int cmd_buf_type; /* Def:of CMD_type Specify type cmd (||, &&, ;) */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Definition of a structure that
 * represents a built-in command.
 * @type: The flag indicating the type of the built-in command.
 * @func: Pointer to the function implementing the built-in command.
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Implementation of the parser */

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);


/* Implementation of the parser */

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);


/* Implementation of the shell loop for the "hsh" program */

int loophsh(char **);

/* Implementation of error handling functions */

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* Implementation of string manipulation functions */

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* Additional implementation of string manipulation functions */

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);


/* Implementation of exit-related functions */

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* Implementation of the tokenizer */

char **strtow(char *, char *);
char **strtow2(char *, char *);

/* Implementation of memory reallocation functions */

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);


/* Implementation of memory management functions */

int bfree(void **);

/* Implementation of the atoi function */

int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* Additional implementation of error handling functions */

int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Implementation of the built-in commands */

int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* Additional implementation of built-in commands */

int _myhistory(info_t *);
int _myalias(info_t *);

/* Implementation of the getline function */

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* Implementation of functions to retrieve information */

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* Implementation of environment-related functions */

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* Implementation of functions to retrieve environment variables */

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* Implementation of history-related functions */

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* Implementation of linked list functions */

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* Additional implementation of linked list functions */

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* Implementation of variable-related functions */

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
