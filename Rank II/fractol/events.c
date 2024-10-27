/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:12:40 by suroh             #+#    #+#             */
/*   Updated: 2024/10/26 17:05:49 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_com(t_fct *fct)
{
	mlx_destroy_image(fct->mlx_con, fct->img.img_ptr);
	mlx_destroy_window(fct->mlx_con, fct->mlx_win);
	mlx_destroy_display(fct->mlx_con);
	free(fct->mlx_con);
	exit(EXIT_SUCCESS);
}

int	keys(int keysym, t_fct *fct)
{
	if (keysym == XK_Escape)
		close_com(fct);
	else if (keysym == XK_Left)
		fct->sft_x += (0.5 * fct->zoom);
	else if (keysym == XK_Right)
		fct->sft_x -= (0.5 * fct->zoom);
	else if (keysym == XK_Up)
		fct->sft_y -= (0.5 * fct->zoom);
	else if (keysym == XK_Down)
		fct->sft_y += (0.5 * fct->zoom);
	else if (keysym == XK_equal)
		fct->itr_def += 10;
	else if (keysym == XK_minus)
		fct->itr_def -= 10;
	fct_rdr(fct);
	return (0);
}

int	mouses(int button, int x, int y, t_fct *fct)
{
	(void)x;
	(void)y;
	if (button == Button4)
	{
		fct->zoom *= 0.95;
	}
	else if (button == Button5)
	{
		fct->zoom *= 1.05;
	}
	fct_rdr(fct);
	return (0);
}

/*The mlx_hook() function tells the MLX library that when a specific event
 * (like a key press, mouse button press, or window close) happens,
 * it should call the function associated with that event. Even though
 * you have declared and defined the close_com() function, you still
 * need to register it with MLX so that MLX knows to call close_com()
 * when the window close event is triggered.
 * Without mlx_hook, MLX would not know which function to call when
 * the window close event happens, even though the function is declared.*/

/*The function exit() is a standard way in C to terminate a program.
 * reasons for exit(); Graceful Termination; Resource Management; Exit Status
 * In C, there are two common exit status codes:
 * EXIT_SUCCESS (usually 0):
 * 	Indicates that the program completed without any errors.
 * EXIT_FAILURE (usually 1):
 * 	Indicates that the program encountered an error during execution.*/

/* Have to put fct_rdr() again in order to render the image again.
 * to refresh the image.*/
