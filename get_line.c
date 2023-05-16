#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
* getline - reads a line from  input
* @linepointer: pointer to a character array that stores the input line
* @ptr: pointer to a size_t  that holds the size of the  array
* @stream: a file pointer to stdin
*
* Return: number of characters read, plus terminating null byte
*/

ssize_t getline(char **linepointer, size_t *ptr, FILE *stream)
{
	static char buffer[BUFF_SIZE];
	static size_t buffer_pos;
	size_t line_pos = 0;
	char c;

	buffer_pos = 0;
	if (*linepointer == NULL)
		*linepointer = malloc(*ptr);
	if (*linepointer == NULL)
		return (-1);
	while (1)
	{
	if (buffer_pos == 0)
	{
		size_t bytes_read = fread(buffer, 1, BUFF_SIZE, stream);
	if (bytes_read == 0)
		return (-1);
	}
	c = buffer[buffer_pos++];
	if (c == '\n' || buffer_pos == BUFF_SIZE)
	{
	(*linepointer)[line_pos++] = '\0';
		*ptr = line_pos;
		buffer_pos = 0;
		return (line_pos);
	}
	(*linepointer)[line_pos++] = c;
	if (line_pos >= *ptr)
	{
	*ptr += BUFF_SIZE;
	*linepointer = realloc(*linepointer, *ptr);
		if (*linepointer == NULL)
			return (-1);
	}
	}
}
