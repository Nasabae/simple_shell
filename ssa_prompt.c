#include "shell.h"

/**
 * ctrl_c - ignore Ctrl-C input and prints prompt again
 * @n: takes in int from signal
 */
void ctrl_c(int n)
{
    (void)n;
    write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * built_in - handles builtins (exit, env, cd)
 * @token: user's typed command
 * @env: environmental variable
 * @num: take in nth user command typed to write error message
 * @command: bring in command to free
 * Return: 1 if acted on builtin, 0 if not
 */
int built_in(char **token, char **env, int num, char **command)
{
    (void)token;
    (void)env;
    (void)num;
    (void)command;

    /* Implementation of built-in commands */
    /* Add your code here */

    return 0;
}

/**
 * ignore_space - return string without spaces in front
 * @str: string
 * Return: new string
 */
char *ignore_space(char *str)
{
    while (*str == ' ')
        str++;
    return str;
}

/**
 * ctrl_D - exits program if Ctrl-D was pressed
 * @i: characters read via get_line
 * @command: user's typed in command
 * @env: environmental variable linked list
 */
void ctrl_D(int i, char *command, char **env)
{
    (void)i;
    (void)command;
    (void)env;

    /* Implementation of ctrl_D function */
    /* Add your code here */
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    ssa_prompt(env);

    return 0;
}
