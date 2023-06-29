#include "shell.h"

/**
 * ssa_myhistory - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int ssa_myhistory(info_t *info)
{
print_list(info->history);
return (0);
}

/**
 * ssa_unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int ssa_unset_alias(info_t *info, char *str)
{
char *p, x;
int ret;
p = strchr(str, '=');
if (!p)
return (1);
x = *p;
*p = 0;
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*p = x;
return (ret);
}

/**
 * ssa_set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int ssa_set_alias(info_t *info, char *str)
{
char *z;
z = strchr(str, '=');
if (!z)
return (1);
if (!*++z)
return (ssa_set_alias(info, str));
ssa_set_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * ssa_print_alias - prints an alias string
 * @node: the alias node
 * Return: ALways 0 on success, 1 on error
 */
int ssa_print_alias(list_t *node)
{
char *p = NULL, *b = NULL;
if (node)
{
p = strchr(node->str, '=');
for (b = node->str; b <= p; b++)
_putchar(*b);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
 * ssa_myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int ssa_myalias(info_t *info)
{
int z = 0;
char *p = NULL;
list_t *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_list(node);
node = node->next;
}
return (0);
}
for (z = 1; info->argv[z]; z++)
{
p = strchr(info->argv[z], '=');
if (p)
ssa_set_alias(info, info->argv[z]);
else
print_list(node_starts_with(info->alias, info->argv[z], '='));
}
return (0);
}
