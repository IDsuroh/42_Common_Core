/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_push_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 00:14:18 by suroh             #+#    #+#             */
/*   Updated: 2024/11/23 00:22:33 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_five(t_stack_node **a, t_stack_node **b)
{
	while (stack_len(*a) > 3)
	{
		node_initiation(*a, *b);
		finish_rotation(a, find_min_node(*a), 'a');
		pb(b, a, false);
	}
}

void	push_swap(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*min_node;
	int				len_a;

	len_a = stack_len(*a);
	if (len_a == 5)
		sort_five(a, b);
}
