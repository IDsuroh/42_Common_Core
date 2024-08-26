/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:46:25 by suroh             #+#    #+#             */
/*   Updated: 2024/05/13 11:45:12 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

void	ft_printf_nbr(int nb, int *char_num)
{
	long int	num;
	char		value;

	num = nb;
	if (num < 0)
	{
		ft_printf_char('-', char_num);
		num *= -1;
	}
	value = (num % 10) + 48;
	num /= 10;
	if (num > 0)
		ft_printf_nbr(num, char_num);
	ft_printf_char(value, char_num);
}

void	ft_printf_nbr_u(unsigned int nb, int *char_num)
{
	char	value;

	value = (nb % 10) + 48;
	nb /= 10;
	if (nb > 0)
		ft_printf_nbr_u(nb, char_num);
	ft_printf_char(value, char_num);
}

void	ft_printf_nbr_base_low(unsigned int nb, int *char_num)
{
	char	*base;
	char	value;

	base = "0123456789abcdef";
	value = base[nb % 16];
	nb /= 16;
	if (nb > 0)
		ft_printf_nbr_base_low(nb, char_num);
	ft_printf_char(value, char_num);
}

void	ft_printf_nbr_base_up(unsigned int nb, int *char_num)
{
	char	*base;
	char	value;

	base = "0123456789ABCDEF";
	value = base[nb % 16];
	nb /= 16;
	if (nb > 0)
		ft_printf_nbr_base_up(nb, char_num);
	ft_printf_char(value, char_num);
}

// Recursive called functions are printed first.
