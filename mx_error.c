#include "shell.h"

/**
 * m_str_cat_cs - function that concatenates the message for cd error
 *
 * @varshell: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @nr_str: counter lines
 * Return: error message
 */
char *m_str_cat_cs(shell_var *varshell, char *msg, char *error, char *nr_str)
{
	char *forbiden_flg;

	_m_strcpy(error, varshell->av[0]);
	_m_strcat(error, ": ");
	_m_strcat(error, nr_str);
	_m_strcat(error, ": ");
	_m_strcat(error, varshell->args[0]);
	_m_strcat(error, msg);
	if (varshell->args[1][0] == '-')
	{
		forbiden_flg = malloc(3);
		forbiden_flg[0] = '-';
		forbiden_flg[1] = varshell->args[1][1];
		forbiden_flg[2] = '\0';
		_m_strcat(error, forbiden_flg);
		free(forbiden_flg);
	}
	else
	{
		_m_strcat(error, varshell->args[1]);
	}

	_m_strcat(error, "\n");
	_m_strcat(error, "\0");
	return (error);
}

/**
 * m_err_get_cd - error message for cd command in get_cd
 * @varshell: data relevant (directory)
 * Return: Error message
 */
char *m_err_get_cd(shell_var *varshell)
{
	int leng, id_len;
	char *error, *nr_str, *msg;

	nr_str = m_itoa(varshell->counter);
	if (varshell->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		id_len = 2;
	}
	else
	{
		msg = ": can't cd to ";
		id_len = _m_len_str(varshell->args[1]);
	}

	leng = _m_len_str(varshell->av[0]) + _m_len_str(varshell->args[0]);
	leng += _m_len_str(nr_str) + _m_len_str(msg) + id_len + 5;
	error = malloc(sizeof(char) * (leng + 1));

	if (error == 0)
	{
		free(nr_str);
		return (NULL);
	}

	error = m_str_cat_cs(varshell, msg, error, nr_str);

	free(nr_str);

	return (error);
}

/**
 * m_err_notfound - generic error message for command not found
 * @varshell: data relevant (counter, arguments)
 * Return: Error message
 */
char *m_err_notfound(shell_var *varshell)
{
	int leng;
	char *error;
	char *nr_str;

	nr_str = m_itoa(varshell->counter);
	leng = _m_len_str(varshell->av[0]) + _m_len_str(nr_str);
	leng += _m_len_str(varshell->args[0]) + 16;
	error = malloc(sizeof(char) * (leng + 1));
	if (error == 0)
	{
		free(error);
		free(nr_str);
		return (NULL);
	}
	_m_strcpy(error, varshell->av[0]);
	_m_strcat(error, ": ");
	_m_strcat(error, nr_str);
	_m_strcat(error, ": ");
	_m_strcat(error, varshell->args[0]);
	_m_strcat(error, ": not found\n");
	_m_strcat(error, "\0");
	free(nr_str);
	return (error);
}

/**
 * m_err_exit_sh - generic error message for exit in get_exit
 * @varshell: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *m_err_exit_sh(shell_var *varshell)
{
	int leng;
	char *error;
	char *nr_str;

	nr_str = m_itoa(varshell->counter);
	leng = _m_len_str(varshell->av[0]) + _m_len_str(nr_str);
	leng += _m_len_str(varshell->args[0]) + _m_len_str(varshell->args[1]) + 23;
	error = malloc(sizeof(char) * (leng + 1));
	if (error == 0)
	{
		free(nr_str);
		return (NULL);
	}
	_m_strcpy(error, varshell->av[0]);
	_m_strcat(error, ": ");
	_m_strcat(error, nr_str);
	_m_strcat(error, ": ");
	_m_strcat(error, varshell->args[0]);
	_m_strcat(error, ": Illegal number: ");
	_m_strcat(error, varshell->args[1]);
	_m_strcat(error, "\n\0");
	free(nr_str);

	return (error);
}

/**
 * m_env_err - error message for env in get_env.
 * @varshell: data relevant (counter, arguments)
 * Return: error message.
 */
char *m_env_err(shell_var *varshell)
{
	int leng;
	char *error;
	char *nr_str;
	char *msg;

	nr_str = m_itoa(varshell->counter);
	msg = ": Unable add/remove from environ\n";
	leng = _m_len_str(varshell->av[0]) + _m_len_str(nr_str);
	leng += _m_len_str(varshell->args[0]) + _m_len_str(msg) + 4;
	error = malloc(sizeof(char) * (leng + 1));
	if (error == 0)
	{
		free(error);
		free(nr_str);
		return (NULL);
	}

	_m_strcpy(error, varshell->av[0]);
	_m_strcat(error, ": ");
	_m_strcat(error, nr_str);
	_m_strcat(error, ": ");
	_m_strcat(error, varshell->args[0]);
	_m_strcat(error, msg);
	_m_strcat(error, "\0");
	free(nr_str);

	return (error);
}
