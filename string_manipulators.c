#include "header.h"

/**
 * free_path_args - a function to free the path and args
 * @path: the path to free
 * @check_path: path status
 * @args: input argument array
 */

void free_path_args(char **path, int *check_path, char ***args)
{
	if ((*check_path) == 1)
		free(*path);
	(*check_path) = 0;
	free_args(args);
}

/**
 * str_comp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: int
 */

int str_comp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0'))
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (-1);
}



/**
 * string_length - a function to return the length of a string
 * @s: a char pointer passed from main
 * Return: returns an int for the length of s
 */


int string_length(char *s)
{
	int len = 0;

	while (s[len] != '\0')
	{
		len++;
		continue;
	}
	return (len);
}

/**
 * string_duplicator - a function to copy a string.
 * @input: argv[0] .
 * @jina: variable
 * Return: a pointer to output.
 */

char *string_duplicator(char *input, char *jina)
{
	int i = 0;

	while (input[i])
	{
		jina[i] = input[i];
		i++;
	}
	jina[i] = '\0';

	return (jina);
}

/**
 * free_args - a function to free the args
 * @args: the arguments
 */

void free_args(char ***args)
{
	int i = 0;

	while ((*args)[i])
	{
		free((*args)[i]);
		i++;
	}
	free((*args)[i]);
	free((*args));
}
