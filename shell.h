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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH '\n'

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for convert_number() */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* 1 if using system getline() */
#define USE_GETLINE     0
#define USE_STRTOK      0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
 * structr passinfo - contains pseudo-arguments to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecout_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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
char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

#ifndef MAX_LINE_LEN
#define MAX_LINE_LEN 1024
#endif



/**
 * struct builtin - contains a builtin string and related function
 * type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

/* exit builtin */
int exit_builtin(info_t *info);

/* _putchar.c */
int _putchar(char c);

/* shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* ssa_errors.c */
void ssa_eputs(char *str);
int ssa_eputchar(char c);
int ssa_putfd(char c, int fd);
int ssa_putsfd(char *str, int fd);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);

/* ssa_exits.c */
char *ssa_strncpy(char *, char *, int);
char *ssa_strncat(char *, char *, int);
char *ssa_strchr(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int bfree(void **);

/*ssa_atoi.c */
int ssa_interactive(info_t *);
int ssa_is_delim(char, char *);
int ssa_isalpha(int);
int ssa_atoi(char *);

/* ssa_errors1.c */
int ssa_erratoi(char *s);
void ssa_print_error(info_t *, char *);
int ssa_print_d(int, int);
char *ssa_convert_number(long int, int, int);
void ssa_remove_comments(char *);

/* ssa_builtin.c */
int ssa_myexit(info_t *);
int ssa_mycd(info_t *);
int ssa_myhelp(info_t *);

/* ssa_builtin1.c */
int ssa_myhistory(info_t *);
int ssa_myalias(info_t *);

/* ssa_getline.c */
ssize_t ssa_get_input(info_t *);
int ssa_getline(info_t *, char **, size_t *);
void ssa_sigintHandler(int);

/* ssa_getinfo.c */
void ssa_clear_info(info_t *);
void ssa_set_info(info_t *, char **);
void ssa_free_info(info_t *, int);

/* ssa_environ.c */
char *ssa_getenv(info_t *, const char *);
int ssa_myenv(info_t *);
int ssa_mysetenv(info_t *);
int ssa_myunsetenv(info_t *);
int ssa_populate_env_list(info_t *);

/* ssa_getenv.c */
char **ssa_get_environ(info_t *);
int ssa_unsetenv(info_t *, char *);
int ssa_setenv(info_t *, char *, char *);

/* ssa_history.c */
char *ssa_get_history_file(info_t *info);
int ssa_write_history(info_t *info);
int ssa_read_history(info_t *info);
int ssa_build_history_list(info_t *info, char *buf, int linecount);
int ssa_renumber_history(info_t *info);

/* lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t len);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/* free info */
void free_info(info_t *info, int flag);

#endif
