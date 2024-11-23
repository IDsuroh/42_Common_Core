/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:53:56 by suroh             #+#    #+#             */
/*   Updated: 2024/11/22 23:29:42 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(t_stack_node **stack)
{
	t_stack_node	*last_node;
	int				len;

	len = stack_len(*stack);
	if (stack == NULL || *stack == NULL || len == 1)
		return ;
	last_node = find_last_node(*stack);
	last_node->links.prev->links.next = NULL;
	last_node->links.next = *stack;
	last_node->links.prev = NULL;
	*stack = last_node;
	last_node->links.next->links.prev = last_node;
}

/* [Node 1] <-> [Node 2] <-> [Node 3] <-> [Node 4]
 * ^stack				    ^last
 * [Node 1] <-> [Node 2] <-> [Node 3] -> NULL	[Node 4]
 * ^stack
 * [Node 1] <-> [Node 2] <-> [Node 3] -> NULL   [Node 4] -> [Node 1]
 * ^stack					  ^last	    ^stack
 * NULL <-> [Node 4] -> [Node 1] <-> [Node 2] <-> [Node 3]
 * 	    ^last	 ^stack
 * [Node 4] -> [Node 1] <-> [Node 2] <-> [Node 3]
 * ^last^stack
 * [Node 4] <-> [Node 1] <-> [Node 2] <-> [Node 3]
 * last line is important because it connects Node 1 to Node 4 (prev button)
 * 	*/

void	rra(t_stack_node **a, bool checker)
{
	reverse_rotate(a);
	if (!checker)
		write(1, "rra\n", 4);
}

//Shift down all elements of stack a by 1.
//The last element becomes the first one.

void	rrb(t_stack_node **b, bool checker)
{
	reverse_rotate(b);
	if (!checker)
		write(1, "rrb\n", 4);
}

//Shift down all elements of stack b by 1.
//The last element becomes the first one.

void	rrr(t_stack_node **a, t_stack_node **b, bool checker)
{
	reverse_rotate(a);
	reverse_rotate(b);
	if (!checker)
		write(1, "rrr\n", 4);
}

//rra and rrb at the same time.
