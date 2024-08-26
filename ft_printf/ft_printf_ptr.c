/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:48:13 by suroh             #+#    #+#             */
/*   Updated: 2024/05/13 12:34:52 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

static void	ft_printf_ptr_printer(uintptr_t ptr, int *char_num)
{
	char	*base;
	char	value;

	base = "0123456789abcdef";
	value = base[ptr % 16];
	ptr /= 16;
	if (ptr > 0)
		ft_printf_ptr_printer(ptr, char_num);
	ft_printf_char(value, char_num);
}

void	ft_printf_ptr(uintptr_t ptr, int *char_num)
{
	if (!ptr)
	{
		ft_printf_str("(nil)", char_num);
	}
	else
	{
		ft_printf_str("0x", char_num);
		ft_printf_ptr_printer(ptr, char_num);
	}
}

// uintptr_t is a fixed-width unsigned integer type.
// It is designed to hold memory addresses as integers.
// Specifically as unsigned integers.
//
// "(nil)" is specific to indicating the absence of a valid memory address.
// The string "(nil)" is a conventional way in C programming to represent
// a null pointer in a human-readable format.
// NULL is also used to represent a null pointer.
// But, it is typically not used as a printable string
// when displaying a null pointer.
