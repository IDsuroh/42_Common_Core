/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_push_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:14:23 by suroh             #+#    #+#             */
/*   Updated: 2024/11/30 00:06:36 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*min_node;
	int				len_a;

	len_a = stack_len(*a);
	if (len_a == 5)
		sort_five(a, b);
	else
	{
		while (len_a-- > 3)
			pb(b, a, false);
	}
	sort_three(a);
	while (*b)
	{
		node_initiation(*a, *b);
		move_nodes(a, b);
	}
	set_current_position(*a);
	min_node = find_min_node(*a);
	if (min_node->info.above_middle == true)
		while (*a != min_node)
			ra(a, false);
	else
		while (*a != min_node)
			rra(a, false);
}
