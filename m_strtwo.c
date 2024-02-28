#include "shell.h"

/**
 * _m_strdup - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *_m_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _m_len_str(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_m_memry_cpy(new, s, len + 1);
	return (new);
}

/**
 * _m_len_str - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int _m_len_str(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * m_cmp_chars - compare chars of strings
 * @str: input string.
 * @delimtr: delimtriter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int m_cmp_chars(char str[], const char *delimtr)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delimtr[j]; j++)
		{
			if (str[i] == delimtr[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _m_strtok - splits a string by some delimtriter.
 * @str: input string.
 * @delimtr: delimtriter.
 *
 * Return: string splited.
 */
char *_m_strtok(char str[], const char *delimtr)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (m_cmp_chars(str, delimtr))
			return (NULL);
		splitted = str; /*Store first address*/
		i = _m_len_str(str);
		str_end = &str[i]; /*Store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimtriter for null char*/
		for (i = 0; delimtr[i]; i++)
		{
			if (*splitted == delimtr[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != delimtr*/
			bool = 1;
	}
	if (bool == 0) /*Str == delimtr*/
		return (NULL);
	return (str_start);
}

/**
 * _m_is_digit - defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _m_is_digit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
