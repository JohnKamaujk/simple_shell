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
