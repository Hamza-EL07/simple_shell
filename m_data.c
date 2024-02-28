#include "shell.h"

/**
 * m_addnodervar - adds a variable at the end
 * of a r_var list.
 * @_mhead: _mhead of the linked list.
 * @l_var: length of the variable.
 * @val: value of the variable.
 * @m_l_val: length of the value.
 * Return: address of the _mhead.
 */
r_var *m_addnodervar(r_var **_mhead, int l_var, char *val, int m_l_val)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = l_var;
	new->val = val;
	new->len_val = m_l_val;

	new->next = NULL;
	temp = *_mhead;

	if (temp == NULL)
	{
		*_mhead = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*_mhead);
}

/**
 * m_freelistrvar - frees a r_var list
 * @_mhead: _mhead of the linked list.
 * Return: no return.
 */
void m_freelistrvar(r_var **_mhead)
{
	r_var *temp;
	r_var *curr;

	if (_mhead != NULL)
	{
		curr = *_mhead;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*_mhead = NULL;
	}
}

/**
 * m_freedata - frees data structure
 *
 * @varshell: data structure
 * Return: no return
 */
void m_freedata(shell_var *varshell)
{
	unsigned int i;

	for (i = 0; varshell->_environ[i]; i++)
	{
		free(varshell->_environ[i]);
	}

	free(varshell->_environ);
	free(varshell->pid);
}

/**
 * m_set_data - Initialize data structure
 *
 * @varshell: data structure
 * @av: argument vector
 * Return: no return
 */
void m_set_data(shell_var *varshell, char **av)
{
	unsigned int i;

	varshell->av = av;
	varshell->input = NULL;
	varshell->args = NULL;
	varshell->status = 0;
	varshell->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	varshell->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		varshell->_environ[i] = _m_strdup(environ[i]);
	}

	varshell->_environ[i] = NULL;
	varshell->pid = m_itoa(getpid());
}
