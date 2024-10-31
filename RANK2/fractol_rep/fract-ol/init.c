/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:45:03 by suroh             #+#    #+#             */
/*   Updated: 2024/10/26 17:06:45 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	malloc_error(void)
{
	perror("Problem with malloc");
	exit(EXIT_FAILURE);
}

static void	data_init(t_fct *fct)
{
	fct->esc_val = 4;
	fct->itr_def = 40;
	fct->sft_x = 0.0;
	fct->sft_y = 0.0;
	fct->zoom = 1.0;
}

static void	events_init(t_fct *fct)
{
	mlx_hook(fct->mlx_win, KeyPress, KeyPressMask, keys, fct);
	mlx_hook(fct->mlx_win, ButtonPress, ButtonPressMask, mouses, fct);
	mlx_hook(fct->mlx_win, DestroyNotify, StructureNotifyMask, close_com, fct);
}

void	fct_init(t_fct *fct)
{
	fct->mlx_con = mlx_init();
	if (NULL == fct->mlx_con)
		malloc_error();
	fct->mlx_win = mlx_new_window(fct->mlx_con, WDT, HGT, fct->name);
	if (NULL == fct->mlx_win)
	{
		mlx_destroy_display(fct->mlx_con);
		free(fct->mlx_con);
		malloc_error();
	}
	fct->img.img_ptr = mlx_new_image(fct->mlx_con, WDT, HGT);
	if (NULL == fct->img.img_ptr)
	{
		mlx_destroy_window(fct->mlx_con, fct->mlx_win);
		mlx_destroy_display(fct->mlx_con);
		free(fct->mlx_con);
		malloc_error();
	}
	fct->img.pixels_ptr = mlx_get_data_addr(fct->img.img_ptr,
			&fct->img.biperpix,
			&fct->img.line_len,
			&fct->img.endian);
	events_init(fct);
	data_init(fct);
}
