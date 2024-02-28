#include "shell.h"

/**
 * m_err_path - error message for path and failure denied permission.
 * @varshell: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *m_err_path(shell_var *varshell)
{
	int leng;
	char *nr_str;
	char *error;

	nr_str = m_itoa(varshell->counter);
	leng = _m_len_str(varshell->av[0]) + _m_len_str(nr_str);
	leng += _m_len_str(varshell->args[0]) + 24;
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
	_m_strcat(error, ": No Permission\n");
	_m_strcat(error, "\0");
	free(nr_str);
	return (error);
}

/**
 * m_get_error - calls the error according the builtin, syntax or permission
 * @varshell: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int m_get_error(shell_var *varshell, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = m_env_err(varshell);
		break;
	case 126:
		error = m_err_path(varshell);
		break;
	case 127:
		error = m_err_notfound(varshell);
		break;
	case 2:
		if (_m_str_cmp("exit", varshell->args[0]) == 0)
			error = m_err_exit_sh(varshell);
		else if (_m_str_cmp("cd", varshell->args[0]) == 0)
			error = m_err_get_cd(varshell);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _m_len_str(error));
		free(error);
	}

	varshell->status = eval;
	return (eval);
}
