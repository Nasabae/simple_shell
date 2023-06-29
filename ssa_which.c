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
    size_t cat_len, str_len, total_len;

    pth = get_env("PATH", env);
    toks = c_str_tok(pth, ":");
    free(pth);

    i = 0;
    while (toks[i] != NULL)
    {
        if (toks[i][0] == '\0')
            cat = getcwd(cat, 0);
        else
            cat = strdup(toks[i]);
        
        cat_len = strlen(cat);
        str_len = strlen(str);
        total_len = cat_len + 1 + str_len + 1;
        cat = realloc(cat, total_len);
        cat[cat_len] = '/';
        strcpy(cat + cat_len + 1, str);
        
        if (access(cat, F_OK) == 0)
        {
            free_double_ptr(toks);
            return cat;
        }
        
        free(cat);
        i++;
    }
    
    free_double_ptr(toks);
    return str;
}
