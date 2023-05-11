#include "monty.h"

int check_valid_instruc(char *s, unsigned int line_number, char *buf)
{
	int i;
	char *valid_command[] = {"push", "pall", "pint", "pop", "swap", "add"};

	for (i = 0; valid_command[i]; i++)
	{
		if (strcmp(valid_command[i], s) == 0)
			return (1);
	}
	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, s);
	free(buf);
	return (-1);
}
