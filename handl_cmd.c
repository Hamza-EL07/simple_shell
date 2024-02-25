#include "shell.h"

/**
 * _get_environ - get an environment variable
 * @env_var: environment variable
 * Return: value of the environment variable
 */

char *_get_environ(const char *env_var)
{
	int i = 0;
	char *k;

	while (environ[i])
	{
		k = strtok(environ[i], "=");
		if (_str_cmp(k, env_var) == 0)
			return (strtok(NULL, "="));
		i++;
	}
	return (NULL);
}

/**
 * parse_cmd - parse a command
 * @cmnd: command to parse
 * @dlm: delimiter
 * Return: array of arguments
 */

char **parse_cmd(char *cmnd, char *dlm)
{
	int arg_num = 0;
	char **tkns;
	char *tokn = strtok(cmnd, dlm);

	tkns = malloc(sizeof(char *) * MAX_ARGS);

	while (tokn != NULL)
	{
		tkns[arg_num++] = tokn;
		tokn = strtok(NULL, dlm);
	}

	tkns[arg_num] = NULL;
	return (tkns);
}

/**
 * check_cmd - check if a command exists in the PATH
 *
 * @cmd: command to check
 * Return: void
 */

char *check_cmd(char *cmd)
{

	char *pth = _get_environ("PATH");
	char *tokn;
	char *cmd_all;
	struct stat st;

	if (_str_chr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (custom_strdup(cmd));
		else
			return (NULL);
	}

	tokn = strtok(pth, ":");
	while (tokn)
	{
		cmd_all = malloc(strlen(tokn) + strlen(cmd) + 2);
		strcpy(cmd_all, tokn);
		strcat(cmd_all, "/");
		strcat(cmd_all, cmd);
		if (stat(cmd_all, &st) == 0)
			return (cmd_all);
		free(cmd_all);
		tokn = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * exec_cmd - execute a command
 * @args: array of arguments
 * Return: void
 */

void exec_cmd(char **args)
{
	pid_t prid;
	char *cmd_path;
	int stat;

	prid = fork();
	if (prid == 0)
	{
		cmd_path = check_cmd(args[0]);
		if (cmd_path)
		{
			execve(cmd_path, args, NULL);
		}
		else
			printf("Command not found\n");
		exit(0);
	}
	else
		waitpid(prid, &stat, 0);
}
