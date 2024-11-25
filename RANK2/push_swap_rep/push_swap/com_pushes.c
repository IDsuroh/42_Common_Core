/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_pushes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 23:34:04 by suroh             #+#    #+#             */
/*   Updated: 2024/11/23 00:02:56 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_stack_node **dest, t_stack_node **src)
{
	t_stack_node	*node2push;

	if (*src == NULL)
		return ;
	node2push = *src;
	*src = (*src)->links.next;
	if (*src)
		(*src)->links.prev = NULL;
	node2push->links.prev = NULL;
	if (*dest == NULL)
	{
		*dest = node2push;
		node2push->links.next = NULL;
	}
	else
	{
		node2push->links.next = *dest;
		node2push->links.next->links.prev = node2push;
		*dest = node2push;
	}
}

/* make temporary pointer 'node2push' and assign first node of src.
 * then assign the first node of the stack src to the second node.
 * if then, stack src still exists, link previous button of second node to NULL
 * so that it becomes the first node.
 * Also, node2push's prev button is set to NULL since it will be the first node
 * of the destination stack.
 * if destination stack is empty first node of destination becomes node2push.
 * then the next button of the first node becomes NULL.
 * if destination stack is not empty, node2push's next points to the first node
 * of the destination stack and then link the prev button of the dest node
 * to node2push.
 * then set *dest to node2push to make it the first node of the stack.
 * 	*/

void	pa(t_stack_node **a, t_stack_node **b, bool checker)
{
	push(a, b);
	if (!checker)
		write(1, "pa\n", 3);
}

//Take the first element at the top of b and put it at the top of a.
//Do nothing if b is empty.

void	pb(t_stack_node **b, t_stack_node **a, bool checker)
{
	push(b, a);
	if (!checker)
		write(1, "pb\n", 3);
}

//Take the first element at the top of a and put it at the top of b.
//Do nothing if a is empty
