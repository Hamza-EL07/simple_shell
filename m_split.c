#include "shell.h"

/**
 * swap_m_ch - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_m_ch(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * m_addnodes - add separators and command lines in the lists
 *
 * @_mhead_s: _mhead of separator list
 * @_mhead_l: _mhead of command lines list
 * @input: input string
 * Return: no return
 */
void m_addnodes(m_sep_list **_mhead_s, m_line_list **_mhead_l, char *input)
{
	int i;
	char *line;

	input = swap_m_ch(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			m_addsepnodeend(_mhead_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			m_addsepnodeend(_mhead_s, input[i]);
			i++;
		}
	}

	line = _m_strtok(input, ";|&");
	do {
		line = swap_m_ch(line, 1);
		m_addlinenodeend(_mhead_l, line);
		line = _m_strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * m_go_to_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @varshell: data structure
 * Return: no return
 */
void m_go_to_next(m_sep_list **list_s, m_line_list **list_l,
									shell_var *varshell)
{
	int loop_sep;
	m_sep_list *ls_s;
	m_line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (varshell->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * m_splt_cmd - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @varshell: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int m_splt_cmd(shell_var *varshell, char *input)
{

	m_sep_list *_mhead_s, *list_s;
	m_line_list *_mhead_l, *list_l;
	int loop;

	_mhead_s = NULL;
	_mhead_l = NULL;

	m_addnodes(&_mhead_s, &_mhead_l, input);

	list_s = _mhead_s;
	list_l = _mhead_l;

	while (list_l != NULL)
	{
		varshell->input = list_l->line;
		varshell->args = m_splt_line(varshell->input);
		loop = m_exc_lin(varshell);
		free(varshell->args);

		if (loop == 0)
			break;

		m_go_to_next(&list_s, &list_l, varshell);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	m_freeseplist(&_mhead_s);
	m_freelinelist(&_mhead_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * m_splt_line - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **m_splt_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _m_strtok(input, TOK_delimtr);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _realloc_dp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _m_strtok(NULL, TOK_delimtr);
		tokens[i] = token;
	}

	return (tokens);
}
