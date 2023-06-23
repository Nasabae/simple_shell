#include "shell.h"

/**
 * ssa_myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * Return: Always 0
 */
int ssa_myenv(info_t *info)
{
print_list_str(info->env);
return (0);
}

/**
 * ssa_getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * @name: env var name
 * Return: the value
 */
char *ssa_getenv(info_t *info, const char *name)
{
list_t *node  = info->env;
char *r;
while (node)
{
r = starts_with(node->str, name);
if (r && *r)
return (r);
node = node->next;
}
return (NULL);
}

/**
 * ssa_mysetenv - Initializes a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * Return: Always 0
 */
int ssa_mysetenv(info_t *info)
{
if (info->argc != 3)
{
_puts("Incorrect number of arguments\n");
return (1);
}
if (ssa_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
 * ssa_myunsetenv - Remove an envirinment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int ssa_myunsetenv(info_t *info)
{
int z;
if (info->argc == 1)
{
_puts("Too few arguments.\n");
return (1);
}
for (z = 1; z <= info->argc; z++)
ssa_unsetenv(info, info->argv[z]);
return (0);
}

/**
 * ssa_populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * Return: Always 0
 */
int ssa_populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t z;
for (z = 0; environ[z]; z++)
add_node_end(&node, environ[z], 0);
info->env = node;
return (0);
}
