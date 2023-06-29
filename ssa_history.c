#include "shell.h"

/**
 * ssa_get_history_file - gets the history file
 * @info: parameter structure
 * Return: allocated string containing history file
 */

char *ssa_get_history_file(info_t *info)
{
char *buf, *dir;
dir = getenv("HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);
return (buf);
}

/**
 * ssa_write_history - creates a file, or appends to an existing file
 * @info: the parameter structure
 * Return: 1 on success, else -1
 */
int ssa_write_history(info_t *info)
{
size_t fd;
char *filename = ssa_get_history_file(info);
list_t *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
_puts(node->str);
_putchar('\n');
}
_puts((char *)BUF_FLUSH);
close(fd);
return (1);
}

/**
 * ssa_read_history - reads history from file
 * @info: the parameter structure
 * Return: history on success, 0 otherwise
 */
int ssa_read_history(info_t *info)
{
int z, last = 0, linecount = 0;
ssize_t fd, rdlength, fsize = 0;
struct stat st;
char *buf = NULL, *filename = ssa_get_history_file(info);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
rdlength = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlength <= 0)
return (free(buf), 0);
close(fd);
for (z = 0; z < fsize; z++)
if (buf[z] == '\n')
{
buf[z] = 0;
ssa_build_history_list(info, buf + last, linecount++);
last = z + 1;
}
if (last != z)
ssa_build_history_list(info, buf + last, linecount++);
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
delete_node_at_index(&(info->history), 0);
ssa_renumber_history(info);
return (info->histcount);
}

/**
 * ssa_build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * @buf: buffer
 * @linecount: the history linecount, history count
 * Return: Always 0
 */
int ssa_build_history_list(info_t *info, char *buf, int linecount)
{
list_t *node = NULL;
if (info->history)
node = info->history;
add_node_end(&node, buf, linecount);
if (!info->history)
info->history = node;
return (0);
}

/**
 * ssa_renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * Return: the new history count
 */
int ssa_renumber_history(info_t *info)
{
list_t *node = info->history;
int z = 0;
while (node)
{
node->num = z++;
node = node->next;
}
return (info->histcount = z);
}
