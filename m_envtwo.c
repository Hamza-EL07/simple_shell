#include "shell.h"

/**
 * copy_m_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_m_info(char *name, char *value)
{
	char *new;
	int len_nm, len_val, len;

	len_nm = _m_len_str(name);
	len_val = _m_len_str(value);
	len = len_nm + len_val + 2;
	new = malloc(sizeof(char) * (len));
	_m_strcpy(new, name);
	_m_strcat(new, "=");
	_m_strcat(new, value);
	_m_strcat(new, "\0");

	return (new);
}

/**
 * set_m_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @varshell: data structure (environ)
 * Return: no return
 */
void set_m_env(char *name, char *value, shell_var *varshell)
{
	int i;
	char *var_env, *nm_env;

	for (i = 0; varshell->_environ[i]; i++)
	{
		var_env = _m_strdup(varshell->_environ[i]);
		nm_env = _m_strtok(var_env, "=");
		if (_m_str_cmp(nm_env, name) == 0)
		{
			free(varshell->_environ[i]);
			varshell->_environ[i] = copy_m_info(nm_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	varshell->_environ = _realloc_dp(varshell->_environ,
																	 i, sizeof(char *) * (i + 2));
	varshell->_environ[i] = copy_m_info(name, value);
	varshell->_environ[i + 1] = NULL;
}

/**
 * _m_setenv - compares env variables names
 * with the name passed.
 * @varshell: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _m_setenv(shell_var *varshell)
{

	if (varshell->args[1] == NULL || varshell->args[2] == NULL)
	{
		m_get_error(varshell, -1);
		return (1);
	}

	set_m_env(varshell->args[1], varshell->args[2], varshell);

	return (1);
}

/**
 * _m_unsetenv - deletes a environment variable
 *
 * @varshell: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _m_unsetenv(shell_var *varshell)
{
	char **realloc_environ;
	char *var_env, *nm_env;
	int i, j, k;

	if (varshell->args[1] == NULL)
	{
		m_get_error(varshell, -1);
		return (1);
	}
	k = -1;
	for (i = 0; varshell->_environ[i]; i++)
	{
		var_env = _m_strdup(varshell->_environ[i]);
		nm_env = _m_strtok(var_env, "=");
		if (_m_str_cmp(nm_env, varshell->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		m_get_error(varshell, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; varshell->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = varshell->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(varshell->_environ[k]);
	free(varshell->_environ);
	varshell->_environ = realloc_environ;
	return (1);
}
