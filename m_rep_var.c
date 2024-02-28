#include "shell.h"

/**
 * m_chck_env - checks if the typed variable is an env variable
 *
 * @h: _mhead of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void m_chck_env(r_var **h, char *in, shell_var *data)
{
	int row, chr, j, m_l_val;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				m_l_val = _m_len_str(_envr[row] + chr + 1);
				m_addnodervar(h, j, _envr[row] + chr + 1, m_l_val);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	m_addnodervar(h, j, NULL, 0);
}

/**
 * m_chck_vars - check if the typed variable is $$ or $?
 *
 * @h: _mhead of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int m_chck_vars(r_var **h, char *in, char *st, shell_var *data)
{
	int i, lst, lpd;

	lst = _m_len_str(st);
	lpd = _m_len_str(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				m_addnodervar(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				m_addnodervar(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				m_addnodervar(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				m_addnodervar(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				m_addnodervar(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				m_addnodervar(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				m_addnodervar(h, 0, NULL, 0);
			else
				m_chck_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * m_replace_input - replaces string into variables
 *
 * @_mhead: _mhead of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *m_replace_input(r_var **_mhead, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *_mhead;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * m_rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @varshell: data structure
 * Return: replaced string
 */
char *m_rep_var(char *input, shell_var *varshell)
{
	r_var *_mhead, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = m_itoa(varshell->status);
	_mhead = NULL;

	olen = m_chck_vars(&_mhead, input, status, varshell);

	if (_mhead == NULL)
	{
		free(status);
		return (input);
	}

	indx = _mhead;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = m_replace_input(&_mhead, input, new_input, nlen);

	free(input);
	free(status);
	m_freelistrvar(&_mhead);

	return (new_input);
}
