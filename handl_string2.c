#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)

{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string to stdout
 * @str: string to print
 *
 * Return: void
 */

void _puts(char *str)
{
	while (*str)
	{
		_putchar(*str);
		str++;
	}
}

/**
 * custom_strdup - duplicate a string
 * @str: string to duplicate
 * Return: pointer to the new string
 */

char *custom_strdup(const char *str)
{
	int length = 0;
	int i = 0;
	char *new_str;

	while (str[length] != '\0')
	{
		length++;
	}

	new_str = (char *)malloc((length + 1) * sizeof(char));

	if (new_str == NULL)
	{
		return (NULL);
	}

	for (i = 0; i <= length; i++)
		new_str[i] = str[i];
	return (new_str);
}
