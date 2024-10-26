/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:54:05 by suroh             #+#    #+#             */
/*   Updated: 2024/10/24 17:56:22 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fct	fct;

	if (2 == ac && !ft_strncmp(av[1], "mandelbrot", 10))
	{
		fct.name = av[1];
		fct_init(&fct);
		fct_rdr(&fct);
		mlx_loop(fct.mlx_con);
	}
	else if (4 == ac && !ft_strncmp(av[1], "julia", 5))
	{
		fct.name = av[1];
		fct.julia_x = atodbl(av[2]);
		fct.julia_y = atodbl(av[3]);
		fct_init(&fct);
		fct_rdr(&fct);
		mlx_loop(fct.mlx_con);
	}
	else
	{
		putstr_fd(ERRMSG, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
