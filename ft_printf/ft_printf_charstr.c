/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_charstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:47:42 by suroh             #+#    #+#             */
/*   Updated: 2024/05/13 12:35:06 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

void	ft_printf_char(int c, int *char_num)
{
	write (1, &c, 1);
	(*char_num)++;
}

void	ft_printf_str(char *str, int *char_num)
{
	if (!str)
	{
		*char_num += write (1, "(null)", 6);
		return ;
	}
	while (*str)
	{
		ft_printf_char(*str, char_num);
		++str;
	}
}

// nil or NULL is not used in this case because,
// NULL represents a 'null pointer' and it's not used to represent
// a 'null string'.
// "The string "(null)" is used to represent the absence of a valid string,
// and it's a common convention in C to do so. 
// It clearly communicates to the user that the input string was NULL and
// there was nothing to print." - ChatGPT
