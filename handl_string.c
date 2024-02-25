#include "shell.h"

/**
 * _str_chr - locates a character in a string
 *@str: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_str_chr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 *  _str_leng - find the length of a string
 * @str: string
 * Return: length of the string
 */

int _str_leng(const char *str)
{
	int leng = 0;

	while (str[leng])
		leng++;
	return (leng);
}

/**
 * _str_cpy - copy a string
 * @target: destination string
 * @sorc: source string
 * Return: pointer to the destination string
 */

char *_str_cpy(char *target, const char *sorc)
{
	char *ptr = target;

	while (*sorc)
		*target++ = *sorc++;
	*target = 0;
	return (ptr);
}

/**
 * _str_cat - concatenate two strings
 * @target: destination string
 * @sorc: source string
 * Return: pointer to the destination string
 */

char *_str_cat(char *target, const char *sorc)
{
	char *ptr = target;

	while (*target)
		target++;
	while (*sorc)
		*target++ = *sorc++;
	*target = 0;
	return (ptr);
}

/**
 * _str_cmp - compare two strings
 * @strone: first string
 * @strtwo: second string
 * Return: 0 if the strings are equal, otherwise the difference
 */

int _str_cmp(const char *strone, const char *strtwo)
{
	while (*strone && *strtwo)
	{
		if (*strone != *strtwo)
			return (*strone - *strtwo);
		strone++;
		strtwo++;
	}
	return (*strone - *strtwo);
}
