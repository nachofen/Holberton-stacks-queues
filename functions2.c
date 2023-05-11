#include "monty.h"

/**
 * monty_push - pushes an element at the top of the stack_t.
 * @stack: The pointer to the top of a stack_t.
 * @line_num: The number of the line.
 * @token: an array of tokens
 * Return: Nothing.
 */
int monty_push(stack_t **stack, char **token, unsigned int line_num)
{
	stack_t *new_node;
	int i = 0;

	if (token[1] == NULL)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_num);
		return (EXIT_FAILURE);
	}
	while (token[1][i])
	{
		if (i == 0 && token[1][i] == '-')
		{
			i++;
			continue;
		}
		if (token[1][i] < '0' || token[1][i] > '9')
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_num);
			free_stack(stack);
			return (EXIT_FAILURE);
		}
		i++;
	}
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = atoi(token[1]);
	new_node->prev = NULL;
	new_node->next = *stack;
	if (*stack != NULL)
	{
		(*stack)->prev = new_node;
	}
	*stack = new_node;
	return (EXIT_SUCCESS);

}
/**
 * monty_pall - prints the values of the stack_t.
 * @stack: The pointer to the top of a stack_t.
 * @line_num: The number of the line.
 * Return: Nothing.
 */
void monty_pall(stack_t **stack, unsigned int line_num)
{
	stack_t *aux = *stack;
	(void) line_num;
	while (aux)
	{
		printf("%d\n", aux->n);
			aux = aux->next;
	}
}
/**
 * monty_pint - prints the value at the top of the stack.
 * @stack: The pointer to the top of a stack_t.
 * @line_number: The number of the line.
 * Return: Nothing.
 */
void monty_pint(stack_t **stack, unsigned int line_number)
{
	if (!*stack)
	{
		fprintf(stderr, "L%d: can\'t pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
/**
 * monty_pop - removes the top element of the stack.
 * @stack: The pointer to the top of a stack_t.
 * @line_number: The number of the line.
 * Return: Nothing.
 */
void monty_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if ((*stack) == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);

}
/**
 * monty_swap - swaps the two top elements of the stack.
 * @stack: The pointer to the top of a stack_t.
 * @line_number: The number of the line.
 * Return: Nothing.
 */
void monty_swap(stack_t **stack, unsigned int line_number)
{
	int aux;

	if ((*stack) == NULL || (*stack)->next == NULL)
	{
		fprintf(stdout, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	aux = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = aux;
}
