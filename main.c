#include "monty.h"

/**
 * main - The entry point function for Monty Interpreter.
 * @ac: The number of arguments.
 * @av: The pointer to an array of inputed arguments.
 * Return: Always 0 (on Success).
 */
int main(int ac, char **av)
{
	FILE *fd = NULL;
	int exit_st = EXIT_SUCCESS;

	if (ac != 2)/*checking number of args*/
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	fd = fopen(av[1], "r");/*open file in readmode*/
	if (fd == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		return (EXIT_FAILURE);
	}
	exit_st = monty_run(fd);
	fclose(fd);
	return (exit_st);
}


