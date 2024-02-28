#include "shell.h"

/**
 * as_ln - assigns the line var for get_ln
 * @ptr_line: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void as_ln(char **ptr_line, size_t *n, char *buffer, size_t j)
{

	if (*ptr_line == NULL)
	{
		if (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*ptr_line = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*ptr_line = buffer;
	}
	else
	{
		_m_strcpy(*ptr_line, buffer);
		free(buffer);
	}
}
/**
 * get_ln - Read inpt from strmfile
 * @ptr_line: buffer that stores the input
 * @n: size of ptr_line
 * @strmfile: strmfile to read from
 * Return: The number of bytes
 */
ssize_t get_ln(char **ptr_line, size_t *n, FILE *strmfile)
{
	int i;
	static ssize_t input;
	ssize_t valret;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(strmfile);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	as_ln(ptr_line, n, buffer, input);
	valret = input;
	if (i != 0)
		input = 0;
	return (valret);
}

/**
 * read_m_line - reads the input string.
 *
 * @meof: return value of getline function
 * Return: input string
 */
char *read_m_line(int *meof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*meof = getline(&input, &bufsize, stdin);

	return (input);
}

#include "shell.h"

/**
 * get_sign_int - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void get_sign_int(int sign)
{
	(void)sign;
	write(STDOUT_FILENO, "\n>-< ", 5);
}

/**
 * get_my_help - function that retrieves help messages according builtin
 * @varshell: data structure (args and input)
 * Return: Return 0
 */
int get_my_help(shell_var *varshell)
{

	if (varshell->args[1] == 0)
		m_gen_help();
	else if (_m_str_cmp(varshell->args[1], "setenv") == 0)
		m_set_m_envhelp();
	else if (_m_str_cmp(varshell->args[1], "env") == 0)
		m_envhelp();
	else if (_m_str_cmp(varshell->args[1], "unsetenv") == 0)
		m_unset_m_envhelp();
	else if (_m_str_cmp(varshell->args[1], "help") == 0)
		m_help();
	else if (_m_str_cmp(varshell->args[1], "exit") == 0)
		m_exithelp();
	else if (_m_str_cmp(varshell->args[1], "cd") == 0)
		m_help_cd();
	else if (_m_str_cmp(varshell->args[1], "alias") == 0)
		m_help_alias();
	else
		write(STDERR_FILENO, varshell->args[0],
					_m_len_str(varshell->args[0]));

	varshell->status = 0;
	return (1);
}
