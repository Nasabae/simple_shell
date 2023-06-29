#include "shell.h"

/**
 * *ssa_strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */
char *ssa_strncpy(char *dest, char *src, int n)
{
int z, x;
char *s = dest;
z = 0;
while (src[z] != '\0' && z < n - z)
{
dest[z] = src[z];
z++;
}
if (z < n)
{
x = z;
while (x < n)
{
*(dest + x) = '\0';
x++;
}
}
return (s);
}

/**
 * *ssa_strncat - concatenates two strings
 * @dest: the first or destination string
 * @src: the second or source string
 * @n: the amount of bytes to be maximally used
 * Return: the concanated string
 */
char *ssa_strncat(char *dest, char *src, int n)
{
int z, x;
char *s = dest;

z = 0;
x = 0;
while (dest[z] != '\0')
z++;
while (src[x] != '\0' && x < n)
{
dest[z] = src[x];
z++;
x++;
}
if (x < n)
dest[z] = '\0';
return (s);
}

/**
 * *ssa_strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: (s) a pointer to the memory area s
 */
char *ssa_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');
return (NULL);
}
