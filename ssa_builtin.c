#include "shell.h"

/**
 * ssa_myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a give exit status
 * (0) if info.argv[0] != "exit"
 */
int ssa_myexit(info_t *info)
{
int exitcheck;
if (info->argv[1]) /* if there is an exit argument */
{
exitcheck = ssa_erratoi(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
ssa_print_error(info, "Illegal number: ");
_puts(info->argv[1]);
_putchar('\n');
return (1);
}
info->err_num = ssa_erratoi(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}

/**
 * ssa_mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int ssa_mycd(info_t *info)
{
char *s, *dir, buffer[1024];
int chdir_ret;
s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = getenv("HOME=");
if (!dir)
chdir_ret = /* TODO: what should this be" */
chdir((dir = getenv("PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!getenv("OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(getenv("OLDPWD=")), _putchar('\n');
chdir_ret = /* TODO: what should this be? */
chdir((dir = getenv("OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
ssa_print_error(info, "can't cd to ");
_puts(info->argv[1]), _putchar('\n');
}
else
{
ssa_setenv(info, "OLDPWD", ssa_getenv(info, "PWD="));
ssa_setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * ssa_myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int ssa_myhelp(info_t *info)
{
char **arg_array;
arg_array = info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array); /*temp att_unused workaround */
return (0);
}
