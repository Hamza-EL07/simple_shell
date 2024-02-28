#include "shell.h"

/**
 * m_repeat_char - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int m_repeat_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (m_repeat_char(input - 1, i + 1));

	return (i);
}

/**
 * m_error_sep_op - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int m_error_sep_op(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (m_error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = m_repeat_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = m_repeat_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (m_error_sep_op(input + 1, i + 1, *input));
}

/**
 * m_frst_ch - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int m_frst_ch(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * m_print_syntx_err - prints when a syntax error is found
 *
 * @varshell: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void m_print_syntx_err(shell_var *varshell, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = m_itoa(varshell->counter);
	length = _m_len_str(varshell->av[0]) + _m_len_str(counter);
	length += _m_len_str(msg) + _m_len_str(msg2) + _m_len_str(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_m_strcpy(error, varshell->av[0]);
	_m_strcat(error, ": ");
	_m_strcat(error, counter);
	_m_strcat(error, msg2);
	_m_strcat(error, msg);
	_m_strcat(error, msg3);
	_m_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * m_check_syntx_err - intermediate function to
 * find and print a syntax error
 *
 * @varshell: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int m_check_syntx_err(shell_var *varshell, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = m_frst_ch(input, &begin);
	if (f_char == -1)
	{
		m_print_syntx_err(varshell, input, begin, 0);
		return (1);
	}

	i = m_error_sep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		m_print_syntx_err(varshell, input, begin + i, 1);
		return (1);
	}

	return (0);
}
