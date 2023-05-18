#include "shell.h"

/**
 * parser - splits given input into multiple string
 * @input_str: given input as a string
 * @args: stores parsed input
 *
 */

void parser(char *input_str, char **args)
{
	char *arg;
	int i = 0;
	int is_space = 1;

	for (i = 0; input_str[i]; i++)
	{
		if (!isspace(input_str[i]))
		{
			is_space = 0;
			break;
		}
	}
	if (is_space)
	{
		args[0] = NULL;
		return;
	}
	i = 0;
	arg = strtok(input_str, " ");
	while (arg)
	{
		args[i++] = arg;
		arg = strtok(NULL, " ");
	}
	args[i] = NULL;
	if (_stringcompare(args[0], "exit") == 0)
		exit(0);
}
