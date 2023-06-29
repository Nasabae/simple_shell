#include "shell.h"

/**
* c_exit - frees user's typed command and linked list before exiting
* @str: user's typed command
* @env: input the linked list of envirnment
*/
void c_exit(char **str, list_t *env)
{
free_double_ptr(str);
free_linked_list(env);
_exit(0);
}

/**
* _execve - execute command user typed into shell
* @s: command user typed
* @holder: The full path of the command
* @env: environmental variable
* @num: nth user command; to be used in error message
* Return: exit status of the child process
*/
int _execve(char **s, char *holder, int num, list_t *env)
{
int status = 0;
pid_t pid = fork();

if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}

if (pid == 0)
{
/* Child process */
if (execve(holder, s, NULL) == -1)
{
not_found(s[0], num, env);
c_exit(s, env);
}
}
else
{
/* Parent process */
wait(&status);
}

return (status);
}

/**
 * check_command_path - Checks if the command is an absolute path and executes
 * @s: The command arguments
 * @env: The environment variable list
 * @num: The command number
 *
 * Return: The exit status of the executed command
 */

int check_command_path(char **s, list_t *env, int num)
{
    char *holder = NULL;
    int t = 0;
    int status = 0; 

    /* Check if command is absolute path */
    if (access(s[0], F_OK) == 0)
    {
        holder = strdup(s[0]);
        t = 1;
    }
    else
    {
        holder = ssa_which(s[0], env);
    }

    /* If not an executable, free and return error */
    if (access(holder, X_OK) != 0)
    {
        not_found(s[0], num, env);
        free(holder);
        free_double_ptr(s);
        return 127;
    }

    status = _execve(s, holder, num, env); 

    free_double_ptr(s);
    if (t == 0)
    {
        free(holder);
    }

    return status;
}
