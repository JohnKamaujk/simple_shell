#include "header.h"

/**
 * exe_fork - can input be executed before fork?
 * @path: double pointer to set path from input after checking PATH (environ)
 * @args: points to array of arguments from input (TheTaghotel juja)
 * @buffer: points to space where line_getter (getline) points to.
 * @returned_status: input status of previous command
 * @lc: current line count
 * @program_name: name of running program/command
 * all this pointers point to a memory space where data is
 * stored eitther from user input data or processed data
 * this memory locations must be freed to avoid memory leaks.
 */

void exe_fork(char **path, char ***args, char **buffer,
int *returned_status, int lc, char **program_name)
{
	int fail_count = 0, path_trailer = 0;
	char *count;
	struct stat buf;

	(*path) = path_checker(path_finder(), (*args)[0], fail_count, &path_trailer);
	if ((*path) == NULL)
	{
		free_args(args);
		free((*buffer));
		malloc_error(program_name);
	}
	*returned_status = stat((*path), &buf);
	if ((*returned_status) != 0 || (Non_Path && path_trailer))
	{
		fail_count++;
		free(*path);
		(*path) = path_checker(path_finder(), (*args)[0], fail_count, &path_trailer);
		*returned_status = stat((*path), &buf);
		if ((*returned_status) != 0 || (Non_Path && path_trailer))
		{
			count = int2char(lc);
			write(STDERR, (*program_name), string_length((*program_name)));
			write(STDERR, ": ", 2);
			write(STDERR, count, string_length(count));
			write(STDERR, ": ", 2);
			write(STDERR, (*args)[0], string_length((*args)[0]));
			write(STDERR, ": not found\n", 12);
			free(count);
			*returned_status = 127;
			return;
		}
	}

	*returned_status = access((*path), X_OK);
	if ((*returned_status) != 0)
	{
		*returned_status = 126;
		perror("");
		return;
	}
}

/**
 * int2char -takes an int and converts it to
 * a character string for printing.
 * @num: an integer to be converted
 * Return: a pointer to coverted character string output.
 */

char *int2char(int num)
{
	char *string = malloc(sizeof(char) * 10);
	int i = 0, digits = 0, base = 10, divider, pwr, tmp;

	if (num == 0)
		string[i] = '0';
	else if (num < 10)
		string[i] = (num + '0');
	else if (num > 10)
	{
		tmp = num;
		while (tmp != 0)
		{
			tmp /= 10;
			digits++;
		}
		for (pwr = digits; pwr > 0; pwr--, i++)
		{
			divider = power(base, pwr);
			tmp = (num / divider);
			if (tmp < 0)
				tmp *= -1;
			string[i] = (tmp + '0');
			num = (num % divider);
		}
		i--;
	}
	i++;
	string[i] = '\0';
	return (string);
}


/**
 * power - a function to return the length of a string
 * @base: a base
 * @exp: out exponent
 * Return: returns an int
 */

int power(int base, int exp)
{
	int i = 1;
	int result = 1;

	for (i = 1; i < exp; i++)
		result *= base;

	return (result);
}



/**
 * executer - handles fork to cild for execution
 * @args: input argv (array of arguments)
 * @path: path is the program_name
 * @buffer: input buffer read to if need to free
 * Return: The exit status of the child, or errno, or 0 for fall back.
 */

int executer(char **path, char ***args, char **buffer)
{
	pid_t pid;
	int status, ex = 0;

	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	else if (pid < 0)
	{
		free((*path));
		free_args(args);
		free((*buffer));
		perror("");
		return (errno);
	}
	else
	{
		ex = execve((*path), (*args), environ);
		if (ex < 0)
		{
			free((*path));
			free_args(args);
			free((*buffer));
			perror("");
			return (errno);
		}
	}
	return (0);
}




/**
 * parsers - separates input string to variables
 * @buffer: input string to separate into arguments
 * @delim: places specific breakpoints for tokenization in buffer
 * Return: points to array of tokenized args or paths
 */

char **parsers(char *buffer, char *delim)
{
	char **args;
	ssize_t i = 0, arg_counter = 0, j = 0, j_store = 0, arg_size = 0, k = 0;

	arg_counter = arg_counting(&buffer, delim);
	args = malloc(sizeof(char *) * (arg_counter + 1));
	if (args == NULL)
		return (NULL);
	for (i = 0; i < arg_counter; i++, j++)
	{
		for (j_store = j, arg_size = 0; Non_Delim; j++)
			arg_size++;
		args[i] = malloc(sizeof(char) * (arg_size + 1));
		if (args[i] == NULL)
		{
			if (i != 0)
			{
				for (i = i - 1; i >= 0; i--)
					free(args[i]);
			}
			free(args);
			return (NULL);
		}
		for (j = j_store, k = 0; Non_Delim; j++, k++)
			args[i][k] = buffer[j];
		if (j_store != 0)
		{
			if (i == (arg_counter - 1) && buffer[j - 1] == '\n')
				k--;
		}
		args[i][k] = '\0';
		if (buffer[j] != '\0')
		{
			while (buffer[j + 1] == delim[0] && delim[0] != ':')
				j++;
		}
	}
	args[i] = NULL;
	return (args);
}
