/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:44:48 by suroh             #+#    #+#             */
/*   Updated: 2024/11/29 22:12:12 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_len(t_stack_node *stack)
{
	int	count;

	if (stack == NULL)
		return (0);
	count = 0;
	while (stack)
	{
		stack = stack->links.next;
		count++;
	}
	return (count);
}

void	add_node(t_stack_node **stack, int nbr)
{
	t_stack_node	*node;
	t_stack_node	*last_node;

	if (stack == NULL)
		return ;
	node = malloc(sizeof(t_stack_node));
	if (node == NULL)
		return ;
	node->links.next = NULL;
	node->info.nbr = nbr;
	if (*stack == NULL)
	{
		*stack = node;
		node->links.prev = NULL;
	}
	else
	{
		last_node = find_last_node(*stack);
		last_node->links.next = node;
		node->links.prev = last_node;
	}
}

/* in the append_node function, the next button of the last_node
 * will be linked as the current appended process, and the previous
 * node of the current node will be linked to the last_node of the stack.
 *      */

t_stack_node	*find_last_node(t_stack_node *head)
{
	if (head == NULL)
		return (NULL);
	while (head->links.next)
		head = head->links.next;
	return (head);
}

/* In the function; find_last_node, it takes the head of the stack, meaning
 * the start of the first node in the doubly linked list.
 * (the start of the stack)
 * so, it returns the last node of the stack since the while loop
 * iterates until the stack reaches NULL.
 *      */

t_stack_node	*find_min_node(t_stack_node *stack)
{
	long			min;
	t_stack_node	*min_node;

	if (stack == NULL)
		return (NULL);
	min = LONG_MAX;
	while (stack)
	{
		if (stack->info.nbr < min)
		{
			min = stack->info.nbr;
			min_node = stack;
		}
		stack = stack->links.next;
	}
	return (min_node);
}

t_stack_node	*return_least_cost(t_stack_node *stack)
{
	if (stack == NULL)
		return (NULL);
	while (stack)
	{
		if (stack->info.least_mov)
			return (stack);
		stack = stack->links.next;
	}
	return (NULL);
}
