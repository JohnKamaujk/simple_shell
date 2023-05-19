#include "header.h"

/**
 * str_comp - compares two strings
 * @s1: input string 1
 * @s2: input string 2
 * Return: integer
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
 * string_duplicator - a function to copy a string.
 * @input: our argv[0] program name.
 * @name: the name variable
 * Return: a pointer to output.
 */

char *string_duplicator(char *input, char *name)
{
	int i;

	for (i = 0; input[i]; i++)
	{
		name[i] = input[i];
	}
	name[i] = '\0';

	return (name);
}

/**
 * string_length - a function to return the length of a string
 * @s: a char pointer passed from main
 * Return: returns an int for the length of s
 */


int string_length(char *s)
{
	int len;

	for (len = 0; s[len] != '\0'; len++)
		continue;

	return (len);
}

/**
 * free_args - a function to free the args
 * @args: the arguments
 */

void free_args(char ***args)
{
	int i = 0;

	for (i = 0; (*args)[i]; i++)
		free((*args)[i]);
	free((*args)[i]);
	free((*args));
}

/**
 * free_path_args - a function to free the path and args
 * @path: the path to free
 * @check_path: path status to check/reset
 * @args: input argument 2D array
 */

void free_path_args(char **path, int *check_path, char ***args)
{
	if ((*check_path) == 1)
		free(*path);
	(*check_path) = 0;
	free_args(args);
}

