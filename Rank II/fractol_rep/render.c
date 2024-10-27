/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:02:14 by suroh             #+#    #+#             */
/*   Updated: 2024/10/27 13:29:23 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	modified_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = ((x * (img->biperpix / 8)) + (y * img->line_len));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static void	man_or_jul(t_cmplx *z, t_cmplx *c, t_fct *fct)
{
	if (!ft_strncmp(fct->name, "julia", 5))
	{
		c->real = fct->julia_x;
		c->i = fct->julia_y;
	}
	else
	{
		c->real = z->real;
		c->i = z->i;
	}
}

static void	pixel_handler(int x, int y, t_fct *fct)
{
	t_cmplx	z;
	t_cmplx	c;
	int		i;
	int		color;

	i = 0;
	z.real = (map(x, -2, +2, WDT) * fct->zoom) + fct->sft_x;
	z.i = (map(y, +2, -2, HGT) * fct->zoom) + fct->sft_y;
	man_or_jul(&z, &c, fct);
	while (i < fct->itr_def)
	{
		z = sum_cmplx(square_cmplx(z), c);
		if ((z.real * z.real) + (z.i * z.i) > fct->esc_val)
		{
			color = map(i, COLOR_BLACK, COLOR_WHITE, fct->itr_def);
			modified_pixel_put(x, y, &fct->img, color);
			return ;
		}
		++i;
	}
	modified_pixel_put(x, y, &fct->img, COLOR_WHITE);
}

/* the z value is being updated on every iteration where it is based
 * on the squaring of its previous value and the addition of c.
 * if ((z.real * z.real) + (z.i * z.i) > fct->esc_val) this if condition
 * is met, it means that the iteration has escaped. Therefore coloring
 * the outside layer of the circles.
 * Also, the z.real and z.i value goes in circles to infinity because
 * of the calculation.
 * If the input is ./fractol mandelbrot, the 'c' in
 * z = sum_cmplx(square_cmplx(z), c) becomes 'z'.
 * But with julia, the real and i value changes. and stayes individual
 * from 'z'.
 * based on the pythagorean theorem where a^2 + b^2 = c^2, and by
 * calculating the real values and i values, we can get the value of
 * c^2. By so, we can get the Hypotenuse of the drawing which is the
 * escape_value. Since the drawing we are dealing with only has the range
 * from -2 to +2 both x and y axis, the escape_value becomes 2*2=4.
 * The c.real and c.i is only activated when the input is for julia.
 */

void	fct_rdr(t_fct *fct)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HGT)
	{
		x = -1;
		while (++x < WDT)
		{
			pixel_handler(x, y, fct);
		}
	}
	mlx_put_image_to_window(fct->mlx_con, fct->mlx_win, fct->img.img_ptr, 0, 0);
}

/*It only calculates the memory offset.
 * The function calculates an offset to locate the correct
 * position in the image buffer where the pixel color
 * should be written.
 * For example, to access the pixel at (x = 2, y = 1):
 *
 *   img->line_len = 20 bytes (one row)
 *   img->biperpix / 8 = 4 bytes (bytes per pixel)
 *   Offset calculation:
 *       offset = (1 * 20) + (2 * 4) = 20 + 8 = 28
 *       So the pixel at (x = 2, y = 1) starts at
 *       	byte 28 in the image buffer.*/

/*The expression img->pixels_ptr + offset adjusts the
 * pointer img->pixels_ptr to point to the exact memory location.
 * Then casts the memory location to a pointer to an unsigned int.
 * Why? Because the color is likely stored as an unsigned int.
 * The dereferencing of the unsigned int *, (*(unsigned int *)),
 * is to access the value stored in the address of the unsigned int *.*/

/*The real values, as you've stated, go from -2 to +2,
 * which is mapped to the width (WDT) of the window.
 * The imaginary values, on the other hand, are often
 * flipped vertically in many visualizations. This is why
 * they start from +2 at the top and go to -2 at the bottom,
 * which is mapped to the height (HGT).*/

/*Point is out of Mandelbrot if it goes to infinity.
 * We can use this condition to the while loop utilizing
 * Pythagorean Theorem (a*a) + (b*b) = (c*c).
 * Hypotenuse, is basically (c*c) * 2.
 * In our case, if Hypotenuse if bigger than 4, it hits
 * infinity value.*/
