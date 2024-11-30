/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:28:15 by suroh             #+#    #+#             */
/*   Updated: 2024/11/29 23:38:18 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_current_position(t_stack_node *stack)
{
	int	i;
	int	middle;

	if (stack == NULL)
		return ;
	middle = stack_len(stack) / 2;
	i = 0;
	while (stack)
	{
		stack->info.position = i;
		if (i <= middle)
			stack->info.above_middle = true;
		else
			stack->info.above_middle = false;
		stack = stack->links.next;
		i++;
	}
}

/* This function gives a position number to every node in the stack.
 * It is important to set current positions to each because the movement
 * efficiency involves whether the number to move is below or above the medium.
 * 	*/

static void	target_setting(t_stack_node *a, t_stack_node *b)
{
	t_stack_node	*target_a_stack;
	t_stack_node	*target;
	long			target_position;

	while (b)
	{
		target_position = LONG_MAX;
		target_a_stack = a;
		while (target_a_stack)
		{
			if (target_a_stack->info.nbr > b->info.nbr
				&& target_a_stack->info.nbr < target_position)
			{
				target_position = target_a_stack->info.nbr;
				target = target_a_stack;
			}
			target_a_stack = target_a_stack->links.next;
		}
		if (target_position == LONG_MAX)
			b->links.target = find_min_node(a);
		else
			b->links.target = target;
		b = b->links.next;
	}
}

/* This function sets the targets of the nodes in stack 'b'.
 * if there are no number that are bigger than the current 'b' node, it will
 * target the smallest node of stack 'a'.
 * if there are numbers that are bigger than the current 'b' node, the
 * while loop of target_a_stack will run and narrow down the range untill there
 * is only one number that is bigger than the current 'b' node, which is
 * the closest biggest number to the current 'b' node.
 * 	*/

void	movement_cost(t_stack_node *a, t_stack_node *b)
{
	int	len_a;
	int	len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (b)
	{
		b->info.mov_cost = b->info.position;
		if ((b->info.above_middle) == false)
			b->info.mov_cost = len_b - (b->info.position);
		if ((b->links.target->info.above_middle) == true)
			b->info.mov_cost += b->links.target->info.position;
		else
			b->info.mov_cost += len_a - (b->links.target->info.position);
		b = b->links.next;
	}
}

/* This function, movement count, counts how many movement cost it will take to
 * push a node from stack 'b' to stack 'a'. This sets a cost of every node in
 * stack 'b'.
 * Cost in this program means how many movements are needed to bring the node
 * to the very top of the stack.
 *
 * if the current movement cost is below middle, the cost of movement becomes,
 * 	the length of stack 'b' - current node's position.
 * 	so if len_b = 9 and current node is 5
 * 		0 <-> 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6 <-> 7 <-> 8 <-> NULL = 9
 * 				      ^
 * cost:	0     1     2     3     4     4     3     2     1
 *
 * 	9 - 5 = 4 || 9 - 6 = 3 || 9 - 7 = 2 || 9 - 8 = 1
 *
 * if the target node of each 'b' node is above middle;
 * 	b's movement cost becomes (current position + target position)
 * if the target node of each target node of 'b' is above middle;
 * 	the target node's position adds up to the movement cost.
 * else
 * 	the target node's position adds up to the reverse movement cost.
 *	*/

void	set_min_cost(t_stack_node *b)
{
	long			fit_nbr;
	t_stack_node	*fit_node;

	if (b == NULL)
		return ;
	fit_nbr = LONG_MAX;
	while (b)
	{
		if (b->info.mov_cost < fit_nbr)
		{
			fit_nbr = b->info.mov_cost;
			fit_node = b;
		}
		b = b->links.next;
	}
	fit_node->info.least_mov = true;
}

/* This function is to find out which node has the least movement cost.
 * This allows which node is the one to be pushed back to the 'a' stack.
 *	*/

void	node_initiation(t_stack_node *a, t_stack_node *b)
{
	set_current_position(a);
	set_current_position(b);
	target_setting(a, b);
	movement_cost(a, b);
	set_min_cost(b);
}

/* This node initiation will run everytime a movement is done.
 * 	*/
