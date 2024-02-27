#include "shell.h"

/**
 * main - the program entry point
 * @argc: the count of arguments passed to main
 * @argv:  the array of arguments passed to main
 *
 * Return: 0 (success)
 */
int main(__attribute__((unused))int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args, **commands;
	int token_count = 0, command_count = 0;
	int f, stat, interactive = isatty(STDIN_FILENO);

	do {
		if (interactive)
			printf("#cisfun$ ");
		read = getline(&line, &len, stdin);

		if (read != -1)
		{
			tokenize_commands(line, &commands, &command_count);
			for (f = 0; f < command_count; i++)
			{
				tokenize_str(commands[f], &args, &token_count);
				stat = handle_commands(args,  &token_count, argv[0], line);
				free_tokens(&args, &token_count);
			}
			free_tokens(&commands, &command_count);
		}
	} while (read != -1 && !feof(stdin));

	free(line);
	free(args);

	return (stat);
}

/**
 * handle_commands - process commands
 * @args: array of command arguments
 * @token_count: pointer to the token count
 * @argv0: name of the program
 * @line: line read
 *
 * Return: void
 */
int handle_commands(char **args, int *token_count, char *argv0, char *line)
{
	char *tmp;
	int val = 0;

	if (args[0] == NULL) /* empty command entered */
		return (0);

	if ((strcmp(args[0], "setenv") == 0) ||
		(strcmp(args[0], "unsetenv") == 0) ||
		(strcmp(args[0], "cd") == 0) ||
		(strcmp(args[0], "env") == 0))
	{
		builtin_commands(args);
		val = changedir(args, argv0);
		print_env(args);
		return (val);
	}
	exit_shell(args, argv0, token_count, line, val);
	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/') ||
		((args[0][0] == '.' && args[0][1] == '.') && args[0][2] == '/'))
		/* if absolute path/ running an executable */
	{
		val = create_child(args, argv0);
	}
	else
	{
		tmp = args[0];
		args[0] = find_command(args[0], argv0);/* returns abs path or NULL */

		if (args != NULL && args[0] != NULL)
		{
			val = create_child(args, argv0);
			free(args[0]);
		}
		else
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv0, 1, tmp);
			val = 127;
		}
	}
	return (val);
}

/**
 * free_tokens - frees memory utilized by tokens and token array
 * @args: the token array
 * @token_count: count of the tokens to free
 *
 * Return: void
 */
void free_tokens(char ***args, int *token_count)
{
	/**
	  *int f;
	  *for (f = 0; f <= *token_count; f++)
	  *{
	  *	free((*args)[f]);
	  *}
	 */
	free(*args);
	(*args) = NULL;
	*token_count = 0;
}

