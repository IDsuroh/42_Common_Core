/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_push_swap_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:14:18 by suroh             #+#    #+#             */
/*   Updated: 2024/11/29 23:59:50 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_both_stacks(t_stack_node **a,
		t_stack_node **b,
		t_stack_node *lowest_cost_node)
{
	while (*a != lowest_cost_node->links.target
		&& *b != lowest_cost_node)
		rr(a, b, false);
	set_current_position(*a);
	set_current_position(*b);
}

static void	reverse_rotate_both_stacks(t_stack_node **a,
		t_stack_node **b,
		t_stack_node *lowest_cost_node)
{
	while (*a != lowest_cost_node->links.target
		&& *b != lowest_cost_node)
		rrr(a, b, false);
	set_current_position(*a);
	set_current_position(*b);
}

void	end_rotation(t_stack_node **stack,
		t_stack_node *top_node,
		char stack_name)
{
	while (*stack != top_node)
	{
		if (stack_name == 'a')
		{
			if (top_node->info.above_middle)
				ra(stack, false);
			else
				rra(stack, false);
		}
		else if (stack_name == 'b')
		{
			if (top_node->info.above_middle)
				rb(stack, false);
			else
				rrb(stack, false);
		}
	}
}

void	move_nodes(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*lowest_cost;

	lowest_cost = return_least_cost(*b);
	if (lowest_cost->info.above_middle
		&& lowest_cost->links.target->info.above_middle)
		rotate_both_stacks(a, b, lowest_cost);
	else if (!(lowest_cost->info.above_middle)
		&& !(lowest_cost->links.target->info.above_middle))
		reverse_rotate_both_stacks(a, b, lowest_cost);
	end_rotation(b, lowest_cost, 'b');
	end_rotation(a, lowest_cost->links.target, 'a');
	pa(a, b, false);
}

void	sort_five(t_stack_node **a, t_stack_node **b)
{
	while (stack_len(*a) > 3)
	{
		node_initiation(*a, *b);
		end_rotation(a, find_min_node(*a), 'a');
		pb(b, a, false);
	}
}
//Setting the current position again in both the
//reversing both stacks function is important because we have
// to update whether the nodes are above or below middle.