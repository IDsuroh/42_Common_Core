/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_algo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:47:31 by suroh             #+#    #+#             */
/*   Updated: 2024/11/23 00:19:48 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	stack_sorted(t_stack_node *stack)
{
	if (stack == NULL)
		return (1);
	while (stack->links.next)
	{
		if (stack->info.nbr > stack->links.next->info.nbr)
			return (false);
		stack = stack->links.next;
	}
	return (true);
}

static t_stack_node	*find_biggest(t_stack_node *stack)
{
	int				biggest;
	t_stack_node	*biggest_node;

	if (stack == NULL)
		return (NULL);
	biggest = INT_MIN;
	while (stack)
	{
		if (stack->info.nbr > biggest)
		{
			biggest = stack->info.nbr;
			biggest_node = stack;
		}
		stack = stack->links.next;
	}
	return (biggest_node);
}

void	sort_three(t_stack_node **a)
{
	t_stack_node	*biggest;

	biggest = find_biggest(*a);
	if (*a == biggest)
		ra(a, false);
	else if ((*a)->links.next == biggest)
		rra(a, false);
	if ((*a)->info.nbr > (*a)->links.next->info.nbr)
		sa(a, false);
}

/* The Turk algorithm:
 * if stack 'a' > 3
 * 	push 'a' node to stack 'b' twice
 * untill stack 'a' =3
 * 	push 'a' node to stack 'b', sorting 'b' in descending order
 * sort three
 * push all 'b' nodes back to stack 'a'
 * complete with smallest number on top
 *
 * if the first node is the highest, rotate stack.
 * if the second node is the highest, reverse rotate stack.
 * if the last node is the higest, swap first and the second node.
 * 	*/
