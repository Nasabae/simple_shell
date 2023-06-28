#include <stdlib.h>
#include "shell.h"

char *c_ignore(char *str)
{
	while (*str == ' ' || *str == '\n')
		str++;
	return str;
}

void non_interactive(list_t *env)
{
	size_t i = 0, n = 0;
	int command_line_no = 0, exit_stat = 0;
	char *command = NULL, *n_command = NULL, **n_line, **token;

	i = get_line(&command);
	if (i == 0)
	{
		free(command);
		exit(0);
	}
	n_command = command;
	command = c_ignore(command);
	n_line = c_str_tok(command, "\n"); /* tokenize each command string */
	if (n_command != NULL)
		free(n_command);
	n = 0;
	while (n_line[n] != NULL)
	{
		command_line_no++;
		token = c_str_tok(n_line[n], " ");
		exit_stat = ssa_built_in(token, env, command_line_no, n_line);
		if (exit_stat)
		{
			n++;
			continue;
		}
		exit_stat = _execve(token, env, command_line_no);
		n++;
	}
	free_double_ptr(n_line);
	free_linked_list(env);
	exit(exit_stat);
}
