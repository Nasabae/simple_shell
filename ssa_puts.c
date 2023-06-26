#include "holberton.h"
/**
 * ssa_puts - prints a string
 * @str: pointer to the string to print
 * Return: void
*/

void ssa_puts(char *str)
{
int i = 0;
while (str[i])
{
	_putchar(str[i]);
	i++;
}
}
