#include "shell.h"

/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *without_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * m_sh_loop - Loop of shell
 * @varshell: data relevant (av, input, args)
 *
 * Return: no return.
 */
void m_sh_loop(shell_var *varshell)
{
	int loop, meof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_m_line(&meof);
		if (meof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (m_check_syntx_err(varshell, input) == 1)
			{
				varshell->status = 2;
				free(input);
				continue;
			}
			input = m_rep_var(input, varshell);
			loop = m_splt_cmd(varshell, input);
			varshell->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

/**
 * m_exc_lin - finds builtins and commands
 *
 * @varshell: data relevant (args)
 * Return: 1 on success.
 */
int m_exc_lin(shell_var *varshell)
{
	int (*builtin)(shell_var *varshell);

	if (varshell->args[0] == NULL)
		return (1);

	builtin = m_get_buil(varshell->args[0]);

	if (builtin != NULL)
		return (builtin(varshell));

	return (cmd_m_exec(varshell));
}

/**
 * m_cd_sh - changes current directory
 *
 * @varshell: data relevant
 * Return: 1 on success
 */
int m_cd_sh(shell_var *varshell)
{
	char *dir;
	int is_hm, is_hm2, is_ddash;

	dir = varshell->args[1];

	if (dir != NULL)
	{
		is_hm = _m_str_cmp("$HOME", dir);
		is_hm2 = _m_str_cmp("~", dir);
		is_ddash = _m_str_cmp("--", dir);
	}

	if (dir == NULL || !is_hm || !is_hm2 || !is_ddash)
	{
		m_cd_to_home(varshell);
		return (1);
	}

	if (_m_str_cmp("-", dir) == 0)
	{
		m_cd_previous(varshell);
		return (1);
	}

	if (_m_str_cmp(".", dir) == 0 || _m_str_cmp("..", dir) == 0)
	{
		m_cd_dot(varshell);
		return (1);
	}

	m_cd_to(varshell);

	return (1);
}
