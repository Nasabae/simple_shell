#include "shell.h"

/**
 * ssa_input_buf - buffers chained commands
 * @info: parameter structure
 * @buf: address of buffer
 * @len: address of length
 * Return: bytes read
 */
ssize_t ssa_input_buf(info_t *info, char **buf, size_t *len)
{
ssize_t z = 0;
size_t len_p = 0;
char *line = NULL;
if (!*len) /* if nothing is left in the buffer, fill it */
{
/*bfree((void **)info->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, ssa_sigintHandler);
#if USE_GETLINE
z = getline(buf, &len_p, stdin);
#else
z = getline(&line, &len_p, stdin);
#endif
if (z > 0)
{
if ((*buf)[z - 1] == '\n')
{
(*buf)[z - 1] = '\0';
z--;
}
info->linecount_flag = 1;
ssa_remove_comments(*buf);
ssa_build_history_list(info, *buf, info->histcount++);
{
*len = z;
info->cmd_buf = buf;
}
}
}
return (z);
}

/**
 * ssa_get_input - gets a line minus the newline
 * @info: parameter structure
 * Return: bytes read
 */
ssize_t ssa_get_input(info_t *info)
{
static char *buf;
static size_t z, x, len;
ssize_t r = 0;
char **buf_p = &(info->arg), *p;
_putchar(BUF_FLUSH);
r = ssa_input_buf(info, &buf, &len);
if (r == -1)
return (-1);
if (len)
{
x = z;
p = buf + z;
check_chain(info, buf, &x, len);
while (x < len)
{
if (is_chain(info, buf, &x))
break;
x++;
}
z = x + 1;
if (z >= len)
{
z = len = 0;
info->cmd_buf_type = CMD_NORM;
}
*buf_p = p;
return (_strlen(p));
}
*buf_p = buf;
return (r);
}

/**
 * ssa_read_buf - reads a buffer
 * @info: parameter structure
 * @buf: buffer
 * @i: size
 * Return: z
 */
ssize_t ssa_read_buf(info_t *info, char *buf, size_t *i)
{
ssize_t z = 0;
if (*i)
return (0);
z = read(info->readfd, buf, READ_BUF_SIZE);
if (z >= 0)
*i = z;
return (z);
}

/**
 * ssa_getline - get the next line of input from STDIN
 * @info: parameter structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int ssa_getline(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t z, len;
size_t x;
ssize_t r = 0, s = 0;
char *p = NULL, *new_pr = NULL, *c;
p = *ptr;
if (p && length)
s = *length;
if (z == len)
z = len = 0;
r = ssa_read_buf(info, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);
c = strchr(buf + z, '\n');
x = c ? 1 + (unsigned int)(c - buf) : len;
new_pr = _realloc(p, s, s ? s + x : x + 1);
if (!new_pr)
return (p ? free(p), -1 : -1);
if (s)
strncat(new_pr, buf + z, x - z);
else
strcpy(new_pr, buf);
s += x - z;
z = x;
p = new_pr;
p = new_pr;
if (length)
*length = s;
*ptr = p;
return (s);
}

/**
 * ssa_sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void ssa_sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
