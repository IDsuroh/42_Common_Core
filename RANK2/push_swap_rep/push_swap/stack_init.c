/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:53:16 by suroh             #+#    #+#             */
/*   Updated: 2024/11/28 14:05:52 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static long	ft_atol(const char *str)
{
	long	num;
	int		negative_checker;
	int		i;

	num = 0;
	negative_checker = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		negative_checker *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * negative_checker);
}

//my atolong function.

void	stack_init(t_stack_node **a, char **argv, bool is_argc_2)
{
	long	nbr;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (is_it_an_error(argv[i]))
			error_free_msg(a, argv, is_argc_2);
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			error_free_msg(a, argv, is_argc_2);
		if (number_repeats(*a, (int)nbr))
			error_free_msg(a, argv, is_argc_2);
		add_node(a, (int)nbr);
		++i;
	}
	if (is_argc_2)
		free_split(argv);
}

/* The stack_init function take a Double Pointer **a because the purpose of the
 * function is likely to initialize a linked list or a stack structure.
 * This involves allocating memory for the first node and assigning the
 * address of that node to the pointer a. To achieve this, the function needs
 * to modify the original pointer a in main.
 * 
 * if stack_init took a single pointer:
 * 	a is modified locally inside the function.
 * 	The change is not reflected back in main because a is passed by value.
 *
 * with a double pointer:
 * 	*a refers to the original pointer a in main.
 * 	By dereferencing the double pointer, the function modifies
 * 	the actual value of a in main.
 * 	*/
/* if flag_argc_2 == true, it will free the newly made array
 * that was made in the int main by split function.
 * after structuring and linking the nodes.
 * 
 * if the "if (error_syntax(argv[i]))" is true, it will send error_free_msg
 * and exit the program. ((error_syntax(argv[i])) == 1) indicates error.
 * */
