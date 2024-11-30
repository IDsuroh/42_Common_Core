/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_rotates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:06:43 by suroh             #+#    #+#             */
/*   Updated: 2024/11/30 00:09:03 by suroh            ###   ########.fr       */
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
// Before rotation:
// +------+     +------+     +------+     +------+     +------+
// | Head | --> |  A   | <-> |  B   | <-> |  C   | <-> |  D   |
// +------+     +------+     +------+     +------+     +------+
//                 ^             ^             ^             ^
//                 |             |             |             |
//           *stack (Head)   A->links.next   B->links.next   C->links.next
//
// last_node = find_last_node(*stack);
// +------+     +------+     +------+     +------+     +------+
// | Head | --> |  A   | <-> |  B   | <-> |  C   | <-> |  D   |
// +------+     +------+     +------+     +------+     +------+
//                                                   		^
//                                                 	    |
//                                            		last_node (D)
//
// last_node->links.next = *stack;
// +------+     +------+     +------+     +------+     +------+     +------+ 
// | Head | --> |  A   | <-> |  B   | <-> |  C   | <-> |  D   | <-> |  A   |
// +------+     +------+     +------+     +------+     +------+     +------+ 
//                 ^                                            	    ^
//                 |                                                    |
//           *stack (Head)                          last_node->links.next
//
// *stack = (*stack)->links.next;
// +------+     +------+     +------+     +------+     +------+     +------+ 
// | Head | --X |  A   | <-> |  B   | <-> |  C   | <-> |  D   | <-> |  A   |
// +------+     +------+     +------+     +------+     +------+     +------+ 
//                 			 ^                                       ^
//               				 |                                   |
//           				*stack (Head)             last_node->links.next
//
// (*stack)->links.prev = NULL;
// +------+     +------+     +------+     +------+     +------+
// | Head | --> |  B   | <-> |  C   | <-> |  D   | --> |  A   |
// +------+     +------+     +------+     +------+     +------+
//                 ^
//                 |
//           New *stack (B)
//
// last_node->links.next->links.prev = last_node;
// last_node->links.next->links.next = NULL;
// +------+     +------+     +------+     +------+     +------+     +------+
// | Head | --> |  B   | <-> |  C   | <-> |  D   | <-> |  A   | <-> | NULL |
// +------+     +------+     +------+     +------+     +------+     +------+
//                 ^                                 ^
//                 |                                 |
//           New *stack (B)                   New tail (A)
//