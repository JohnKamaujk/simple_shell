#include "header.h"


/**
 * line_reader - is a function meant to read input from STDIN and
 * copy it into a buffer. The fuction should also check for errors
 * in reading, realloc if the input exceeds the buffer and return
 * a count of all it added into the buffer.
 * 
 * @buffsize: set size of buffer allocation
 * @buffer: a pointer to the buffer allocated in main.c
 * @stdin: take input from stdin
 * @user_input: Our indicator that we are in interactive mode.
 * @stat_check: the status check value to see if the last call
 * @program_name: a pointer to the name of our program.
 * 
 * Return: number of bytes read
 */

ssize_t line_reader(char **buffer, ssize_t *buffsize, FILE *stdin,
		 int user_input, int stat_check, char **program_name)
{
	ssize_t rd = 0, count = 0;
	char newline[1] = {'\n'};
	(void)stdin;

	if (buffer == NULL || buffsize == NULL)
	{
		free((*buffer));
		error_readliner(program_name);
	}
	rd = read(STDIN, *buffer, *buffsize);
	if (rd < 0)
	{
		free((*buffer));
		error_readliner(program_name);
	}
	else if (rd == 0)
	{
		free((*program_name));
		free((*buffer));
		if (user_input)
			write(STDOUT, newline, string_length(newline));
		exit(stat_check);
	}
	count += rd;
	while (rd == *buffsize && last != '\0' && last != '\n')
	{
		*buffer = _realloc(*buffer, count);
		rd = read(STDIN, &(*buffer)[count], *buffsize);
		if (rd < 0)
		{
			free(*buffer);
			error_readliner(program_name);
		}
		else if (rd == 0)
			break;
		count += rd;
	}
	(*buffer)[count] = '\0';
	return (count);
}

/**
 * newline - a function to continue the shell without trying to execute program
 * @buffer: buffer with input read into shell
 * @args: 2D array with arguments, including program program_name
 * @sts: input status of previous command
 * @program_name: program_name of currently running shell program
 */

void newline(char **buffer, char ***args, int *sts, char **program_name)
{
	(void)buffer;
	(void)args;
	(void)sts;
	(void)program_name;
}

/**
 * arg_counting - function to count number of arguments based on deliminator
 * @buffer: input string to find argument count of
 *
 * @delim: input deliminator separating arguments
 *
 * Return: number of arguments
 */

ssize_t arg_counting(char **buffer, char *delim)
{
	ssize_t arg_count = 0, i = 0;

	while ((*buffer)[0] == delim[0] && delim[0] != ':')
	{
		(*buffer)++;
	}
	if ((*buffer)[0] != '\0' || delim[0] == ':')
	{
		arg_count++;
		if (delim[0] == ':' && str_comp((*buffer), "\0") == 0)
			return (arg_count);
	}
	for (i = 0; (*buffer)[i]; i++)
	{
		if ((*buffer)[i] == '\n' && i != 0)
		{
			(*buffer)[i] = delim[0];
			break;
		}
		if ((*buffer)[i] == delim[0])
		{
			arg_count++;
			while ((*buffer)[i + 1] == delim[0] && delim[0] != ':')
				i++;
			if ((*buffer)[i + 1] == '\n' || (*buffer)[i + 1] == '\0')
			{
				(*buffer)[i + 1] = delim[0];
				arg_count--;
				return (arg_count);
			}
		}
	}
	return (arg_count);
}

/**
 * goodbye - a fucntion to free remaining memory and exit
 * @buffer: the user input string from getline
 * @args: the tokenized array of arguments
 * @sts: input status of previous command
 * @program_name: program_name of currently running program
 */

void goodbye(char **buffer, char ***args, int *sts, char **program_name)
{
	int i;

	for (i = 0; (*args)[i]; i++)
		free((*args)[i]);
	free((*args)[i]);
	free((*args));
	free((*program_name));
	free((*buffer));

	exit(*sts);
}
