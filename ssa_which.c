#include "shell.h"

/**
* ssa_which - fleshes out command by appending it to a matching PATH directory
* @str: first command user typed into shell (e.g. "ls" if user typed "ls -l")
* @env: environmental variable
* Return: a copy of fleshed out command (e.g. "/bin/ls" if originally "ls")
*/
char *ssa_which(char *str, list_t *env)
{
char *pth, *cat = NULL, **toks;
int i = 0;

/* get and tokenize PATH directories, then free original string */
pth = get_env("PATH", env);
toks = c_str_tok(pth, ":");
free(pth);

/* append "/cmd" to each token to see it's legit */
i = 0;
while (toks[i] != NULL)
{
if (toks[i][0] == '\0')
cat = getcwd(cat, 0);
else
cat = strdup(toks[i]);
size_t cat_len = strlen(cat);
size_t str_len = strlen(str);
size_t total_len = cat_len + 1 + str_len + 1;
/* +1 for '/' and +1 for null terminator */
cat = realloc(cat, total_len);
/* Reallocate memory to  hold the concatenated string */
cat[cat_len] = '/';  /* Add '/' at the end of the original string*/
strcpy(cat + cat_len + 1, str);  /* Copy the command string after '/' */
if (access(cat, F_OK) == 0)
{
/* free tokens before returning legit fleshed path */
free_double_ptr(toks);
return (cat);
}
free(cat); /* free concatenated string if cmd is never found */
i++;
}
free_double_ptr(toks);
return (str); /* return string if not found; won't pass execve */
}
