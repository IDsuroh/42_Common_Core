/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_average.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:57:06 by suroh             #+#    #+#             */
/*   Updated: 2024/05/11 16:34:08 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

float	ft_average(int n, ...) // ... means ellipses
{
	va_list	ap;
	int	total;
	int	i;
	
	va_start(ap, n);
	total = 0;
	i = 0;
	while (i < n)
	{
		total += va_arg(ap, int);
		++i;
	}
	va_end(ap);
	return ((float)total / n);
}

void	ft_printf_char(int c, int *char_num)
{
	write (1, &c, 1);
	(*char_num)++;
}

void	ft_printf_str(char *str, int *char_num)
{
	if (!str)
	{
		write (1, "(null)", 6);
		*char_num += 6;
		return ;
	}
	while (*str)
	{
		ft_printf_char(*str, char_num);
		++str;
	}
	(*char_num)++;
}

void	ft_printf_nbr(int nb, int *char_num)
{
	long int	num;
	char	value;
	
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

void	ft_printf_nbr_base_x(unsigned int nb, int *char_num)
{
	char	*base;
	char	value;

	base = "0123456789abcdef";
	value = base[nb % 16];
	nb /= 16;
	if (nb > 0)
		ft_printf_nbr_base_x(nb, char_num);
	ft_printf_char(value, char_num);
}

// void	ft_printf_nbr_base_x(unsigned int nb, int *counter)
// {
// 	char	*symbols;

// 	symbols = "0123456789ABCDEF";
// 	if (nb < 16)
// 		ft_printf_char(symbols[nb], counter);
// 	else
// 	{
// 		ft_printf_nbr_base_x(nb / 16, counter);
// 		ft_printf_nbr_base_x(nb % 16, counter);
// 	}
// }

void	ft_putptr(unsigned long int n, int *counter)
{
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 16)
		ft_printf_char(symbols[n], counter);
	else
	{
		ft_putptr(n / 16, counter);
		ft_putptr(n % 16, counter);
	}
}

void	ft_ptr(unsigned long int ptr, int *counter)
{
	if (!ptr)
		ft_printf_str("(nil)", counter);
	else
	{
		ft_printf_str("0x", counter);
		ft_putptr(ptr, counter);
	}
}

int	main()
{
	
	int	char_num = 0;
	ft_printf_str("string\n", &char_num);
	printf("\n");
	ft_printf_nbr(123, &char_num);
	printf("\n");
	char_num = printf("%X\n", INT_MIN);
	printf("char_num = %d\n", char_num);
	char_num = printf("%x\n", INT_MIN);
	printf("char_num = %d\n", char_num);
	char_num = 0;
	ft_printf_nbr_base_x(INT_MIN, &char_num);
	printf("\n");
	printf("char_num = %d\n", char_num);
	printf("\n");
	char_num = printf("%d\n", INT_MIN);
	printf("char_num = %d\n", char_num);
	char_num = printf("%d\n", INT_MIN);
	printf("char_num = %d\n", char_num);
	char_num = 0;
	ft_printf_nbr(INT_MIN, &char_num);
	printf("\n");
	printf("char_num = %d\n", char_num);
	printf("\n");
	char_num = printf("%s\n", "14242000");
	printf("char_num = %d\n", char_num);
	char_num = printf("%s\n", "14242000");
	printf("char_num = %d\n", char_num);
	char_num = 0;
	ft_printf_str("14242000", &char_num);
	printf("\n");
	printf("char_num = %d\n", char_num);
	ft_printf_str("string\n", &char_num);
	printf("\n");
	char_num = 0;
	char	str[] = "abc";
	char_num = printf("%p\n", str);
  	printf("%d\n", char_num);
	char_num = 0;
	ft_ptr((unsigned long int)&str, &char_num);
	printf("%d\n", char_num);
	printf("\n");
}