#include "shell.h"

/**
 * m_addsepnodeend - adds a separator found at the end
 * of a m_sep_list.
 * @_mhead: _mhead of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the _mhead.
 */
m_sep_list *m_addsepnodeend(m_sep_list **_mhead, char sep)
{
	m_sep_list *new, *temp;

	new = malloc(sizeof(m_sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
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
 * m_freeseplist - frees a m_sep_list
 * @_mhead: _mhead of the linked list.
 * Return: no return.
 */
void m_freeseplist(m_sep_list **_mhead)
{
	m_sep_list *temp;
	m_sep_list *curr;

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
 * m_addlinenodeend - adds a command line at the end
 * of a m_line_list.
 * @_mhead: _mhead of the linked list.
 * @line: command line.
 * Return: address of the _mhead.
 */
m_line_list *m_addlinenodeend(m_line_list **_mhead, char *line)
{
	m_line_list *new, *temp;

	new = malloc(sizeof(m_line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
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
 * m_freelinelist - frees a m_line_list
 * @_mhead: _mhead of the linked list.
 * Return: no return.
 */
void m_freelinelist(m_line_list **_mhead)
{
	m_line_list *temp;
	m_line_list *curr;

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
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
	int count = 0, i, j;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
