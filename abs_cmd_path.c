#include "shell.h"

/**
 * find_command - finds command from PATH
 * @cmd: the command to search
 * @argv0: name of the program
 *
 * Return: if command found, absolute path to it otherwise NULL
 */
char *find_command(const char *cmd, char *argv0)
{
	char *path, *path_copy, *dir, *result = NULL;
	char executable_path[BUFFER_SIZE];

	path = getenv("PATH"); /*path = get_env("PATH");*/
	if (path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, 1, cmd);
		exit(127);
	}

	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("Error: PATH copy error\n");
		exit(EXIT_FAILURE);
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(executable_path, BUFFER_SIZE, "%s/%s", dir, cmd);

		if (access(executable_path, X_OK) == 0)
		{	/* allocate memory and copy executable_path to it */
			result = (char *)malloc(strlen(executable_path) + 1);
			if (result == NULL)
			{
				perror("Error: Memory allocation error\n");
				exit(EXIT_FAILURE);
			}
			strcpy(result, executable_path);
			break; /* exit loop when valid path is found */
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);

	return (result);
}

