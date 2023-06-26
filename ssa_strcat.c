#include "shell.h"

/**
 * ssa_strcat - concatenate two strings
 * @dest: string to be appended to
 * @src: string to append
 * Return: concatenated string
 */
char *ssa_strcat(char *dest, char *src)
{
	int len = 0;
	int len2 = 0;
	int total_len = 0;
	int j = 0;

	/* find total length of both strings to _realloc */
	while (dest[len] != '\0')
	{
		len++;
		total_len++;
	}
	while (src[len2] != '\0')
	{
		len2++;
		total_len++;
	}

	/* _realloc because dest was malloced outside of function */
	dest = ssa_realloc(dest, len, sizeof(char) * total_len + 1);

	while (src[j] != '\0')
	{
		dest[len] = src[j];
		len++;
		j++;
	}
	dest[len] = '\0';

	return (dest);
}
