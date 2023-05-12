#include "shell.h"

/**
 * _stringtokenize - tokenizes  string
 * @string: the string to be tokenized
 * @delimeter: the delimiter
 * Return: a pointer to next token
 */
char *_stringtokenize(char *string, const char *delimeter)
{
	static char *last_char;
	char *token;
	const char *delim_position;

	if (string)
		last_char = string;
	if (!*last_char)
		return (NULL);
	token = last_char;
	while (*last_char)
	{
		delim_position = delimeter;
		while (*delim_position)
		{
			if (*last_char == *delim_position)
			{
				*last_char = '\0';
				last_char++;
				if (*token)
					return (token);
				token = last_char;
				break;
			}
			delim_position++;
		}
		last_char++;
	}
	return (token);
}

/**
  * _stringcompare - Compares two different strings
  * @str1: The first string
  * @str2: The second string
  *
  * Return: int value 1 when same , 0 false
  */


int _stringcompare(char *str1, char *str2)
{
	int i = 0, j = 0, k = 0;
	int ret;
	int limit;

	while (str1[i])
	{
		i++;
	}
	while (str2[j])
	{
		j++;
	}
	if (i <= j)
	{
		limit = i;
	}
	else
	{
		limit = j;
	}
	while (k <= limit)
	{
		if (str1[k] == str2[k])
		{
			k++;
			continue;
		}
		else
		{
			ret = str1[k] - str2[k];
			break;
		}
	}
	return (ret);
}
