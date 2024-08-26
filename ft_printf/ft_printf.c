/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:53:03 by suroh             #+#    #+#             */
/*   Updated: 2024/05/13 12:16:01 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"

int	ft_format_reader(char c, va_list ap)
{
	int	char_num;

	char_num = 0;
	if (c == 'c')
		ft_printf_char(va_arg(ap, int), &char_num);
	else if (c == 's')
		ft_printf_str(va_arg(ap, char *), &char_num);
	else if (c == 'p')
		ft_printf_ptr(va_arg(ap, uintptr_t), &char_num);
	else if (c == 'd' || c == 'i')
		ft_printf_nbr(va_arg(ap, int), &char_num);
	else if (c == 'u')
		ft_printf_nbr_u(va_arg(ap, unsigned int), &char_num);
	else if (c == 'x')
		ft_printf_nbr_base_low(va_arg(ap, unsigned int), &char_num);
	else if (c == 'X')
		ft_printf_nbr_base_up(va_arg(ap, unsigned int), &char_num);
	else if (c == '%')
		ft_printf_char('%', &char_num);
	return (char_num);
}

static int	ft_flag_check(char char_after, char *flags)
{
	while (*flags)
	{
		if (*flags == char_after)
			return (1);
		flags++;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		char_num;
	va_list	ap;

	va_start(ap, format);
	char_num = 0;
	while (*format)
	{
		if (*format == '%')
		{
			if (ft_flag_check(*++format, FLAGS) == 1)
				char_num += ft_format_reader(*format, ap);
		}
		else
			char_num += write (1, format, 1);
		format++;
	}
	va_end(ap);
	return (char_num);
}

// int	main(void)
// {
// 	int counter1;
// 	int counter3;
// 	int counter4;
// 	int counter5;
// 	int counter6;
// 	int counter7;
// 	int counter8;
// 	int counter9;
// 	int counter10;
// 	int counter12;
// 	int counter13;
// 	int counter14;
// 	int counter15;
// 	int counter16;
// 	int counter17;
// 	int counter18;
// 	void *str = 0;
// 	ft_printf("%p\n", &str);
// 	printf("%p\n\n", &str);
//  	counter10 = printf("%c", 't');
// 	ft_printf("\n");
// 	counter12 = printf("%d\n", INT_MAX);
// 	counter13 = printf("%i\n", INT_MAX);
// 	counter14 = printf("%u\n", INT_MAX);
// 	counter15 = printf("%p\n", &str);
// 	counter16 = printf("%x\n", 16);
// 	counter17 = printf("%X\n", INT_MAX);
// 	counter18 = printf("%%\n\n");
// 	counter1 = ft_printf("%c", 't');
// 	ft_printf("\n");
// 	counter3 = ft_printf("%d\n", INT_MAX);
// 	counter4 = ft_printf("%i\n", INT_MAX);
// 	counter5 = ft_printf("%u\n", INT_MAX);
// 	counter6 = ft_printf("%p\n", &str);
// 	counter7 = ft_printf("%x\n", 16);
// 	counter8 = ft_printf("%X\n", INT_MAX);
// 	counter9 = ft_printf("%%\n\n");	
// 	printf("1 %d\n", counter10);
// 	printf("2 %d\n", counter12);
// 	printf("3 %d\n", counter13);
// 	printf("4 %d\n", counter14);
// 	printf("5 %d\n", counter15);
// 	printf("6 %d\n", counter16);
// 	printf("7 %d\n", counter17);
// 	printf("8 %d\n\n", counter18);
// 	printf("1 %d\n", counter1);
//  	printf("2 %d\n", counter3);
// 	printf("3 %d\n", counter4);
// 	printf("4 %d\n", counter5);
// 	printf("5 %d\n", counter6);
// 	printf("6 %d\n", counter7);
// 	printf("7 %d\n", counter8);
// 	printf("8 %d\n\n", counter9);
// } 
