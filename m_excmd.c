#include "shell.h"

/**
 * is_m_cdir - checks ":" if is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_m_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _m_which - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *_m_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _get_m_env("PATH", _environ);
	if (path)
	{
		ptr_path = _m_strdup(path);
		len_cmd = _m_len_str(cmd);
		token_path = _m_strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_m_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _m_len_str(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_m_strcpy(dir, token_path);
			_m_strcat(dir, "/");
			_m_strcat(dir, cmd);
			_m_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _m_strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_m_executable - determines if is an executable
 *
 * @varshell: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_m_executable(shell_var *varshell)
{
	struct stat st;
	int i;
	char *input;

	input = varshell->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	m_get_error(varshell, 127);
	return (-1);
}

/**
 * chck_m_err_cmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @varshell: data structure
 * Return: 1 if there is an error, 0 if not
 */
int chck_m_err_cmd(char *dir, shell_var *varshell)
{
	if (dir == NULL)
	{
		m_get_error(varshell, 127);
		return (1);
	}

	if (_m_str_cmp(varshell->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			m_get_error(varshell, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(varshell->args[0], X_OK) == -1)
		{
			m_get_error(varshell, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_m_exec - executes command lines
 *
 * @varshell: data relevant (args and input)
 * Return: 1 on success.
 */
int cmd_m_exec(shell_var *varshell)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void)wpd;

	exec = is_m_executable(varshell);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _m_which(varshell->args[0], varshell->_environ);
		if (chck_m_err_cmd(dir, varshell) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _m_which(varshell->args[0], varshell->_environ);
		else
			dir = varshell->args[0];
		execve(dir + exec, varshell->args, varshell->_environ);
	}
	else if (pd < 0)
	{
		perror(varshell->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	varshell->status = state / 256;
	return (1);
}
