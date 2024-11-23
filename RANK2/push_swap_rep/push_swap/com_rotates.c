/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:06:43 by suroh             #+#    #+#             */
/*   Updated: 2024/11/22 22:52:33 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack_node **stack)
{
	t_stack_node	*last_node;
	int				len;

	len = stack_len(*stack);
	if (stack == NULL || *stack == NULL || len == 1)
		return ;
	last_node = find_last_node(*stack);
	last_node->links.next = *stack;
	*stack = (*stack)->links.next;
	(*stack)->links.prev = NULL;
	last_node->links.next->links.prev = last_node;
	last_node->links.next->links.next = NULL;
}

/* [Node1] <-> [Node2] <-> [Node3]
 *  ^stack
 *
 *   *stack points to Node1 (the first node).
 *   Node1->links.next points to Node2.
 *   Node3->links.next is NULL (end of the stack).
 *	last_node will be [Node 3]
 *	[Node 3]'s next will be pointed to [Node 1]
 *	[Node 1] <-> [Node 2] <-> [Node 3] -> [Node 1]
 *			^stack
 *	NULL <-> [Node 2] <-> [Node 3] -> [Node 1]
 *				Last
 *	NULL <-> [Node 2] <-> [Node 3] <-> [Node 1] <-> NULL
 *	Final : [Node 2] <-> [Node 3] <-> [Node 1]			
 * */

void	ra(t_stack_node **a, bool checker)
{
	rotate(a);
	if (!checker)
		write(1, "ra\n", 3);
}

// Shift up all elements of stack a by 1.
//The first element becomes the last one.

void	rb(t_stack_node **b, bool checker)
{
	rotate(b);
	if (!checker)
		write(1, "rb\n", 3);
}

//Shift up all elements of stack a by 1.
//The first element becomes the last one.

void	rr(t_stack_node **a, t_stack_node **b, bool checker)
{
	rotate(a);
	rotate(b);
	if (!checker)
		write(1, "rr\n", 3);
}

//ra and rb at the same time.
