/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:27:27 by suroh             #+#    #+#             */
/*   Updated: 2024/11/28 17:25:55 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_split(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL || *argv == NULL)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

/* this funciton frees the temporarily made arrays by the split function.
 * 	*/

void	free_stack(t_stack_node **stack)
{
	t_stack_node	*tmp;
	t_stack_node	*current;

	if (stack == NULL)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->links.next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

/* this functions frees the stack itself as a whole, since the 'while (current)'
 * checks until the NULL at the end of the stack and frees the current stack
 * by linking the connection of the next in the temporary stack.
 * This process will repeat until tmp = NULL, then current = NULL.
 * Lastly, the whole stack will be NULL. just like how the stack was
 * initiated in the int main.
 * 	*/

void	error_free_msg(t_stack_node **a, char **argv, bool is_argc_2)
{
	free_stack(a);
	if (is_argc_2)
		free_split(argv);
	write (2, "Error\n", 6);
	exit(1);
}

/* this frees both stack a and frees the input of argv[1] if bool is true.`
 * 	*/

int	is_it_an_error(char *nbr_still_str)
{
	int	i;

	if (!(*nbr_still_str == '+'
			|| *nbr_still_str == '-'
			|| (*nbr_still_str >= '0' && *nbr_still_str <= '9')))
		return (1);
	if ((*nbr_still_str == '+'
			|| *nbr_still_str == '-')
		&& !(nbr_still_str[1] >= '0' && nbr_still_str[1] <= '9'))
		return (1);
	i = 0;
	if (nbr_still_str[0] == '+' || nbr_still_str[0] == '-')
		i = 1;
	while (nbr_still_str[i])
	{
		if (!(nbr_still_str[i] >= '0' && nbr_still_str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

/* there are two if conditions;
 * 	#1: checks the very first of the string if they are '+', '-', or a digit.
 * 	#2: checks if it is just a symbol '+', '-', or a digit doesnt follow after.
 *		(e.g.) "+123", "-45" would work but not "-", "+", "+abc"
 *	*/

int	number_repeats(t_stack_node *a, int nbr)
{
	if (a == NULL)
		return (0);
	while (a)
	{
		if (a->info.nbr == nbr)
			return (1);
		a = a->links.next;
	}
	return (0);
}

/* this checks if there are same numbers repeating in the input.
 * 	*/
