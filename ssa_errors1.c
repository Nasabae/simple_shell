#include "shell.h"

/**
 * ssa_erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
int ssa_erratoi(char *s)
{
int z = 0;
unsigned long int result = 0;
if (*s == '+')
s++;  /* TODO: why does this make main return 255? */
for (z = 0;  s[z] != '\0'; z++)
{
if (s[z] >= '0' && s[z] <= '9')
{
result *= 10;
result += (s[z] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}

/**
 * ssa_print_error - prints an error message
 * @info: the parameter & return info structure
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void ssa_print_error(info_t *info, char *estr)
{
_puts(info->fname);
_puts(": ");
printf("Line count: %d\n", info->line_count);
_puts(": ");
_puts(info->argv[0]);
_puts(": ");
_puts(estr);
}

/**
 * ssa_print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 * Return: number of characters printed
 */
int ssa_print_d(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int z, total = 0;
unsigned int _abss_, current;
if (fd == STDERR_FILENO)
__putchar = _putchar;
if (input < 0)
{
_abss_ = -input;
__putchar('-');
total++;
}
else
_abss_ = input;
current = _abss_;
for (z = 1000000000; z > 1; z /= 10)
{
if (_abss_ / z)
{
__putchar('0' + current / z);
total++;
}
current %= z;
}
__putchar('0' + current);
total++;
return (total);
}

/**
 * ssa_convert_number - converter function
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *ssa_convert_number(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long z = num;
if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
z = -num;
sign = '-';
}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';
do	{
*--ptr = array[z % base];
z /= base;
} while (z != 0);
if (sign)
*--ptr = sign;
return (ptr);
}

/**
 * ssa_remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0;
 */
void ssa_remove_comments(char *buf)
{
int z;
for (z = 0; buf[z] != '\0'; z++)
if (buf[z] == '#' && (!z || buf[z - 1] == ' '))
{
buf[z] = '\0';
break;
}
}
