#include "monty.h"

/**
 * monty_run - A function that runs a Monty bytecodes script
 * @fd: File descriptor
 * Return: EXIT_SUCCESS on success, or EXIT_FAILURE on error.
 */
int monty_run(FILE *fd)
{
	stack_t *stack = NULL;
	char *line = NULL, **token = NULL, delim[] = " \t\n";
	size_t len = 0;
	unsigned int line_num = 0, exit_st = EXIT_SUCCESS;

	while (getline(&line, &len, fd) != -1)
	{
		line_num++;
		if (just_del(line, delim))
			continue;
		token = tokenize_line(line, delim);
		if (strcmp(token[0], "nop") == 0)
		{
			free(token);
			continue;
		}
		else if (strcmp(token[0], "push") == 0)
			exit_st = monty_push(&stack, token, line_num);
		else
			exit_st = execute(token, &stack, line_num);
		free(token);
		if (exit_st == EXIT_FAILURE)
			break;
	}
	free_stack(&stack);
	free(line);

	return (exit_st);
}
/**
 * just_del - checks if the line only contains delimiters.
 * @line: the pointer to the line.
 * @delims: string with delimiter characters.
 * Return: 1 if the line only contains delimiters, otherwise 0.
 */
int just_del(char *line, char *delims)
{
	int i, j;

	for (i = 0; line[i]; i++)
	{
		for (j = 0; delims[j]; j++)
		{
			if (line[i] == delims[j])
				break;
		}
		if (delims[j] == '\0')
			return (0);
	}

	return (1);
}
/**
 * execute - Function that checks for a command "opcode" and execute it
 * if theres a match.
 * @token: the opcode to execute.
 * @stack: Doubly linked list representation of a stack.
 * @line_num: line where the opcode was found.
 * Return: EXIT_SUCCESS in success, or EXIT_FAILURE on failure
 */

int execute(char **token, stack_t **stack, unsigned int line_num)
{
	unsigned int i = 0;

	instruction_t op[] = {
		{"pall", monty_pall},
		{"pint", monty_pint},
		{"pop", monty_pop},
		{"swap", monty_swap},
		{"add", monty_add},
		{"null", NULL}
	};

	for (i = 0; i < 6; i++)
	{
		if (strcmp(op[i].opcode, token[0]) == 0)
		{
			op[i].f(stack, line_num);
			return (EXIT_SUCCESS);
		}
	}
	free_stack(stack);
	fprintf(stderr, "L%i: unknown instruction %s\n", line_num, token[0]);
	return (EXIT_FAILURE);
}

/**
 * free_stack - A function that frees the memory allocated for stack
 * @stack: Pointer to linked list representation of a stack
 */

void free_stack(stack_t **stack)
{
	stack_t *aux = *stack;

	if (*stack == NULL)
		return;
	while (*stack)
	{
		aux = (*stack)->next;
		free(*stack);
		*stack = aux;
	}
}
/**
 * tokenize_line - A function that tokenize the line.
 * @line: pointer to the line.
 * @delim: Array with delimiters
 * Return: The pointer to tokens.
 */
char **tokenize_line(char *line, char *delim)
{
	char *tokens = NULL, **tokens_array = NULL;
	int i = 0;
	size_t buffer_size;

	if (line == NULL)
		return (NULL);
	buffer_size = strlen(line);
	if (buffer_size == 0)
		return (NULL);
	tokens_array = malloc((buffer_size) * sizeof(char *));
	if (tokens_array == NULL)
	{
		free(line);
		free(tokens_array);
		printf("Error: malloc failed");
		exit(EXIT_FAILURE);
	}

	tokens = strtok(line, delim);
	if (tokens == NULL)
	{
		free(tokens_array);
		free(line);
		return (NULL);
	}
	while (tokens)
	{
		tokens_array[i] = tokens;
		tokens = strtok(NULL, delim);
		i++;
	}
	tokens_array[i] = '\0';/*adding \0 at  the end*/
	return (tokens_array);
}
