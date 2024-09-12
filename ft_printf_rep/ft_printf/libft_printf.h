/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:51:23 by suroh             #+#    #+#             */
/*   Updated: 2024/05/11 17:03:16 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>

# ifndef FLAGS
#  define FLAGS "csdiupxX%"
# endif

int		ft_printf(const char *format, ...);
int		ft_format_reader(char c, va_list ap);
void	ft_printf_char(int c, int *char_num);
void	ft_printf_str(char *str, int *char_num);
void	ft_printf_ptr(uintptr_t ptr, int *char_num);
void	ft_printf_nbr(int nb, int *char_num);
void	ft_printf_nbr_u(unsigned int nb, int *char_num);
void	ft_printf_nbr_base_low(unsigned int nb, int *char_num);
void	ft_printf_nbr_base_up(unsigned int nb, int *char_num);

#endif