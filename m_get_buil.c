#include "shell.h"

/**
 * m_exit_sh - exits the shell
 *
 * @varshell: data relevant (status and args)
 * Return: 0 on success.
 */
int m_exit_sh(shell_var *varshell)
{
	unsigned int tatus;
	int _isdig;
	int str_len;
	int bignum;

	if (varshell->args[1] != NULL)
	{
		tatus = _m_atoi(varshell->args[1]);
		_isdig = _m_is_digit(varshell->args[1]);
		str_len = _m_len_str(varshell->args[1]);
		bignum = tatus > (unsigned int)INT_MAX;
		if (!_isdig || str_len > 10 || bignum)
		{
			m_get_error(varshell, 2);
			varshell->status = 2;
			return (1);
		}
		varshell->status = (tatus % 256);
	}
	return (0);
}

/**
 * m_get_buil - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*m_get_buil(char *cmd))(shell_var *)
{
	m_builtin_t buil[] = {
			{"env", _env},
			{"exit", m_exit_sh},
			{"setenv", _m_setenv},
			{"unsetenv", _m_unsetenv},
			{"cd", m_cd_sh},
			{"help", get_my_help},
			{NULL, NULL}};
	int i;

	for (i = 0; buil[i].name; i++)
	{
		if (_m_str_cmp(buil[i].name, cmd) == 0)
			break;
	}

	return (buil[i].f);
}

/**
 * m_get_len - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */
int m_get_len(int n)
{
	unsigned int n1;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		lenght++;
		n1 = n1 / 10;
	}

	return (lenght);
}
/**
 * m_itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *m_itoa(int n)
{
	unsigned int n1;
	int lenght = m_get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';
	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
		n1 = n;
	lenght--;
	do {
		*(buffer + lenght) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lenght--;
	} while (n1 > 0);
	return (buffer);
}

/**
 * _m_atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _m_atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;
		if (*(s + count) == '-')
			pn *= -1;
		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
