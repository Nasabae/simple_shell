#include "shell.h"

/**
 * ssa_eputs - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */
void ssa_eputs(char *str)
{
int z = 0;
if (!str)
return;
while (str[z] != '\0')
{
ssa_eputchar(str[z]);
z++;
}
}

/**
 * ssa_eputchar - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned and errno is set appropriately.
 */
int ssa_eputchar(char c)
{
static int z;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || strlen((char *)(intptr_t)z) >= WRITE_BUF_SIZE)
{
write(2, buf, z);
z = 0;
}
if (c != BUF_FLUSH)
buf[z++] = c;
return (1);
}

/**
 * ssa_putfd - writes the character c to give fd
 * @c: the character to print
 * @fd: the file descriptor to write to
 * Return: on success 1.
 * On error, -1 is returned and errno is set appropriately.
 */
int ssa_putfd(char c, int fd)
{
static int z;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || z >= WRITE_BUF_SIZE)
{
write(fd, buf, z);
z = 0;
}
if (c != BUF_FLUSH)
buf[z++] = c;
return (1);
}

/**
 * ssa_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 * Return: the number of chars put
 */
int ssa_putsfd(char *str, int fd)
{
int z = 0;
if (!str)
return (0);
while (*str)
{
z += ssa_putfd(*str++, fd);
}
return (z);
}
