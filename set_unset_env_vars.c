#include "shell.h"

/**
 * builtin_commands - handles shell builtin commands
 * @args: arguments to pass to the commands
 *
 * Return: void
 */
void builtin_commands(char **args)
{
	set_env(args);
	unset_env(args);
}

/**
 * set_env - set env variable
 * @args: array of arguments to work with
 *
 * Return: void (no return type)
 */
void set_env(char **args)
{
	if (strcmp(args[0], "setenv") == 0)
	{
		if (args[1] != NULL && args[2] != NULL && args[3] == NULL)
		{
			if (setenv(args[1], args[2], 1) != 0)
			{
				fprintf(stderr, "setenv: unable to set env variable\n");
			}
		}
		else
		{
			fprintf(stderr, "setenv: wrong values\n");
		}
	}
}

/**
 * unset_env - unset an environment variable
 * @args: array containing arguments to work with
 *
 * Return: void
 */
void unset_env(char **args)
{
	if (strcmp(args[0], "unsetenv") == 0)
	{
		if (args[1] != NULL && args[2] == NULL)
		{
			if (unsetenv(args[1]) != 0)
			{
				fprintf(stderr, "unsetenv: Unable to unset env variable\n");
			}
		}
		else
		{
			fprintf(stderr, "unsetenv: wrong values\n");
		}
	}
}


