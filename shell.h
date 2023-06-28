#ifndef SHELL
#define SHELL

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/**
 * struct list - linked list for environmental variables
 * @var: holds environmental variable string
 * @string: holds environmental variable value
 * @next: points to next node
 */
typedef struct list
{
char *var;
char *string;
struct list *next;

} list_t;

/* function prototypes */
int ssa_prompt(char **env);
void *ssa_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
size_t get_line(char **str);
int ssa_t_strlen(char *str, int pos, char delm);
char *ssa_ignore_space(char *str);
char **ssa_str_tok(char *str, char *delm);
char **c_str_tok(char *str, char *delm);
char *ssa_strcat(char *dest, char *src);
char *ssa_strdup(char *str);
char *ssa_strcpy(char *dest, char *src);
int ssa_strcmp(char *s1, char *s2);
int _cd(char **str, list_t *env, int num);
int ssa_built_in(char **token, list_t *env, int num, char **command);
void non_interactive(list_t *env);
char *ssa_which(char *str, list_t *env);
int __exit(char **s, list_t *env, int num, char **command);
void free_double_ptr(char **str);
void free_linked_list(list_t *list);
int _env(char **str, list_t *env);
char *get_env(char *str, list_t *env);
list_t *env_linked_list(char **env);
list_t *add_end_node(list_t **head, char *str);
size_t print_list(list_t *h);
int delete_nodeint_at_index(list_t **head, int index);
int ssa_unsetenv(list_t **env, char **str);
int ssa_setenv(list_t **env, char **str);
int ssa_find_env(list_t *env, char *str);
void not_found(char *str, int num, list_t *env);
void cant_cd_to(char *str, int c_n, list_t *env);
void illegal_number(char *str, int c_n, list_t *env);
char *int_to_string(int num);
int _execve(char **s, char *holder, int num, list_t *env);
int check_command_path(char **s, list_t *env, int num);

#endif
