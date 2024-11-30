/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:26:38 by suroh             #+#    #+#             */
/*   Updated: 2024/11/29 22:11:58 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include "libft/libft.h"

// the structs can be confusing but I think this part as a button.
typedef struct s_stack_links
{
	struct s_stack_node	*target;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}	t_stack_links;

// and this part as the literal info of the node.
typedef struct s_stack_info
{
	int		nbr;
	int		position;
	int		mov_cost;
	bool	least_mov;
	bool	above_middle;
}	t_stack_info;

// the term "node" is like a container that contains data.
typedef struct s_stack_node
{
	t_stack_links	links;
	t_stack_info	info;
}	t_stack_node;

/******************************************************************/

// {error_commands.c}
int				is_it_an_error(char *nbr_still_str);
int				number_repeats(t_stack_node *a, int nbr);
void			free_split(char **argv);
void			free_stack(t_stack_node **stack);
void			error_free_msg(t_stack_node **a, char **argv, bool is_argc_2);

// initiating the stack {stack_init.c}
void			stack_init(t_stack_node **a, char **argv, bool is_argc_2);

// {stack_utils.c}
int				stack_len(t_stack_node *stack);
void			add_node(t_stack_node **stack, int nbr);
t_stack_node	*find_last_node(t_stack_node *head);
t_stack_node	*find_min_node(t_stack_node *stack);
t_stack_node	*return_least_cost(t_stack_node *stack);

// {sort_three_algo.c}
void			sort_three(t_stack_node **a);
bool			stack_sorted(t_stack_node *stack);

//Commands
// {push_swap_init.c}
void			set_current_position(t_stack_node *stack);
void			movement_cost(t_stack_node *a, t_stack_node *b);
void			set_min_cost(t_stack_node *b);
void			node_initiation(t_stack_node *a, t_stack_node *b);

// {com_push_swap_utils.c}
void			move_nodes(t_stack_node **a, t_stack_node **b);
void			sort_five(t_stack_node **a, t_stack_node **b);
void			end_rotation(t_stack_node **stack,
					t_stack_node *top_node,
					char stack_name);

// {com_push_swap.c}
void			push_swap(t_stack_node **a, t_stack_node **b);

// {com_swaps.c}
void			sa(t_stack_node **a, bool checker);
void			sb(t_stack_node **b, bool checker);
void			ss(t_stack_node **a, t_stack_node **b, bool checker);

// {com_rotates.c}
void			ra(t_stack_node **a, bool checker);
void			rb(t_stack_node **b, bool checker);
void			rr(t_stack_node **a, t_stack_node **b, bool checker);

// {com_rev_rotates.c}
void			rra(t_stack_node **a, bool checker);
void			rrb(t_stack_node **b, bool checker);
void			rrr(t_stack_node **a, t_stack_node **b, bool checker);

// {com_pushes.c}
void			pa(t_stack_node **a, t_stack_node **b, bool checker);
void			pb(t_stack_node **b, t_stack_node **a, bool checker);

#endif

/* arrays and structs are different cuz structs can have different type of
 * elements.
 * the struct, contains the 'value', 'current position' (the metadata),
 * and the pointers to the next or the prev. (like a + - button)
 * This allows us to make a 'linked list' which is a series of nodes
 * """CHAINED""" to each other inside the heap.
 * 	*/
