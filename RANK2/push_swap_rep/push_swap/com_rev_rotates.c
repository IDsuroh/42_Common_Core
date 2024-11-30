/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_rev_rotates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:53:56 by suroh             #+#    #+#             */
/*   Updated: 2024/11/29 23:09:51 by suroh            ###   ########.fr       */
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
//Initial state of Stack;
// Before reverse rotation:
//
// +------+     +------+     +------+     +------+
// |  A   | --> |  B   | --> |  C   | --> |  D   |
// +------+     +------+     +------+     +------+
//   *stack       A->next       B->next       C->next
//     ^                                        ^
//     |                                        |
//   A->prev = NULL                         D->next = NULL
//
// last_node = find_last_node(*stack);
// +------+     +------+     +------+     +------+
// |  A   | --> |  B   | --> |  C   | --> |  D   |
// +------+     +------+     +------+     +------+
//                                              ^
//                                              |
//                                            last_node
//
// last_node->links.prev->links.next = NULL;
// After detaching the last node:
//
// +------+     +------+     +------+           +------+
// |  A   | --> |  B   | --> |  C   | --> NULL  |  D   |
// +------+     +------+     +------+           +------+
//   *stack                                     last_node
//
// last_node->links.next = *stack;
// last_node->links.prev = NULL;
// +------+         +------+     +------+     +------+
// |  D   | -->     |  A   | --> |  B   | --> |  C   |
// +------+         +------+     +------+     +------+
//   *stack         A->next       B->next       C->next
//
// last_node->links.next->links.prev = last_node;
// Final state of the stack:
//
// +------+     +------+     +------+     +------+
// |  D   | --> |  A   | --> |  B   | --> |  C   |
// +------+     +------+     +------+     +------+
//   *stack       A->prev       B->prev       C->prev
//