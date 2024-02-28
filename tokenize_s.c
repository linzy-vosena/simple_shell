#include "shell.h"

/**
 * tokenize_str - get tokens froma given string
 * @str: the inout string
 * @tokenarr: the array to store the tokens
 * @token_count: keeps count of all generated tokens
 *
 * Return: void
 */
void tokenize_str(char *str, char ***tokenarr, int *token_count)
{
	int count = 0;
	int size; /* track capacity of array */
	const char delimiter[] = " \t\r\n\a";
	char *token;

	if (str == NULL) /* ensure string is not NULL */
	{
		*token_count = 0;
		return;
	}

	size = TOKEN_BUFSIZE;
	*tokenarr = malloc(size * sizeof(char *));
	/* initialize first strtok_r call */
	token = strtok(str, delimiter);

	while (token != NULL)
	{
		(*tokenarr)[count] = token;
		count++;

		/* only reallocate memory of array when needed */
		if (count >= size)
		{
			size += TOKEN_BUFSIZE;
			*tokenarr = realloc(*tokenarr, size * sizeof(char *));

			if (*tokenarr == NULL)
			{
				fprintf(stderr, "tokenarr realloc error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delimiter);
	}
	/*Add null to the end of the token*/
	(*tokenarr)[count] = NULL;

	*token_count = count;
}

/**
 * tokenize_commands - get separate commands
 * @str: the string to get the commands from
 * @commands: the commands array
 * @command_count: count of the commands obtained
 *
 * Return: void
 */
void tokenize_commands(char *str, char ***commands, int *command_count)
{
	int count = 0;
	int size;
	const char delimiter[] = ";\n";
	char *cmd;

	if (str == NULL)
	{
		*command_count = 0;
		return;
	}

	size = TOKEN_BUFSIZE;
	*commands = malloc(size * sizeof(char *));
	cmd = strtok(str, delimiter);

	while (cmd != NULL)
	{
		(*commands)[count] = cmd;
		count++;

		if (count >= size)
		{
			size += TOKEN_BUFSIZE;
			*commands = realloc(*commands, size * sizeof(char *));

			if (*commands == NULL)
			{
				fprintf(stderr, "commands realloc error\n");
				exit(EXIT_FAILURE);
			}
		}
		cmd = strtok(NULL, delimiter);
	}
	(*commands)[count] = NULL;

	*command_count = count;
}


