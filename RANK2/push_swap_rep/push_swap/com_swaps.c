/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:19:47 by suroh             #+#    #+#             */
/*   Updated: 2024/11/21 21:59:11 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack_node **head)
{
	int	len;

	len = stack_len(*head);
	if (*head == NULL || head == NULL || len == 1)
		return ;
	*head = (*head)->links.next;
	(*head)->links.prev->links.prev = *head;
	(*head)->links.prev->links.next = (*head)->links.next;
	if ((*head)->links.next)
		(*head)->links.next->links.prev = (*head)->links.prev;
	(*head)->links.next = (*head)->links.prev;
	(*head)->links.prev = NULL;
}

/* head, is a pointer. at first it will point to the node next to the current.
 * Then in the second line;
 * 	(*head)->links.prev is the first node.
 *	Set first node->links.prev to point to second node.
 *
 *	(*head)->links.prev is Node 1. Node 1->links.prev is then set to Node 2.
 *	So, Node 2 comes first than Node 1.
 *	[Node2] -> [Node1]
 * After;
 *	since head(Node2)'s next is NULL, head's prev, Node 1, has its next
 *	pointed to NULL.
 * Then,
 * 	Node 2's next is set to Node 1. and Node 2's prev is set to NULL.
 * 	[Node2] <-> [Node1]
 * 	^head.
 *
 * if there is a third node;(if the head's next button is not NULL)
 * 	(Second node)head's next button is the third node and the prev button
 * 	is the first node.
 * 	So, it is directly linking Node 1 to Node 3.
 * 	update Node 3's prev button to Node 1.
 * Then head(Node 2)'s next will be the prev (Node 1) and head's prev will be
 * 	NULL.
 * Thus, completing this visualization.
 *
 * 	[Node2] <-> [Node1] <-> [Node3]
 *	 ^head
 * 	
 * 	*/	

void	sa(t_stack_node **a, bool checker)
{
	swap(a);
	if (!checker)
		write(1, "sa\n", 3);
}

// swap the first 2 elements at the top of stack a.

void	sb(t_stack_node **b, bool checker)
{
	swap(b);
	if (!checker)
		write(1, "sb\n", 3);
}

//Swap the first 2 elements at the top of stack b.

void	ss(t_stack_node **a, t_stack_node **b, bool checker)
{
	swap(a);
	swap(b);
	if (!checker)
		write(1, "ss\n", 3);
}

//sa and sb at the same time.
