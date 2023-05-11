#include "monty.h"

/**
 * monty_add - adds the two top elements of the stack.
 * The result is stored in the second top element of the stack
 * and the top element is removed
 * @stack: The pointer to the top of a stack_t.
 * @line_number: The number of the line.
 * Return: Nothing.
 */
void monty_add(stack_t **stack, unsigned int line_number)
{
	int total;

	if ((*stack) == NULL || (*stack)->next == NULL)
	{
		fprintf(stdout, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	total = (*stack)->n + (*stack)->next->n;
	monty_pop(stack, line_number);
	(*stack)->n = total;
}
