#include "header.h"

/**
 * realocater - a function to double the size of the buffer
 * if the original buffer runs out of room.
 * @buffer: a buffer allocated in shelly to be filled with
 * @count: a count of how many bytes have been read thus
 * far so we know the current buffsize.
 * outin put from stdin
 * Return: a pointer with a filed buffer.
 */

char *realocater(char *buffer, size_t count)
{
	size_t size = count, i = 0;
	char *newbuff = malloc((2 * size) * sizeof(char));

	if (newbuff == NULL)
	{
		free(buffer);
		error_mallocexit();
	}
	for (i = 0; i < size; i++)
		newbuff[i] = buffer[i];
	free(buffer);
	buffer = newbuff;

	return (buffer);
}


/**
 * reset - resets buffer
 * @buffer: input buffer
 * @args: inputarray of arguments for first command
 * @delim: input string with the delimiter used to set args
 * @lc: pointer to our current line count
 * Return: new pointer to buffer, starts from next command or NULL
 */

char *reset(char **buffer, char ***args, char *delim, int *lc)
{
	char *tempbuffer = (*buffer);
	char *newbuffer;
	int i = 0, j = 0;

	for (i = 0; (*args)[i]; i++)
	{
		while (tempbuffer[0] == delim[0])
			tempbuffer++;
		for (j = 0; (*args)[i][j]; j++)
			tempbuffer++;
		if (tempbuffer[0] != '\0')
		{
			while (tempbuffer[0] == delim[0] || tempbuffer[0] == '\n')
			{
				if (tempbuffer[0] == '\n')
					*lc += 1;
				tempbuffer++;
			}
		}
	}
	if (tempbuffer[0] == '\0')
	{
		free((*buffer));
		return (NULL);
	}
	newbuffer = malloc(sizeof(char) * (string_length(tempbuffer) + 1));
	if (newbuffer == NULL)
	{
		free((*buffer));
		free_args(args);
		error_mallocexit();
	}
	for (i = 0; tempbuffer[i] != '\0'; i++)
		newbuffer[i] = tempbuffer[i];
	newbuffer[i] = '\0';
	free((*buffer));

	return (newbuffer);
}

/**
 * _atoi - converts a string to an integer
 * @str: the string to convert
 *
 * Return: the converted integer value
 */

int _atoi(const char *str)
{
	int sign = 1;
	int result = 0;

	/* Skip leading whitespace */
	while (*str == ' ' || *str == '\t')
	{
		str++;
	}

	/* Handle optional sign */
	if (*str == '-' || *str == '+')
	{
		sign = (*str == '-') ? -1 : 1;
		str++;
	}

	/* Convert digits to integer */
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}

	return (result * sign);
}

