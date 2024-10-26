/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 20:16:15 by suroh             #+#    #+#             */
/*   Updated: 2024/10/24 17:20:51 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(double i, double new_min, double new_max, double win_max)
{
	return ((new_max - new_min) * (i) / win_max + new_min);
}

t_cmplx	sum_cmplx(t_cmplx z1, t_cmplx z2)
{
	t_cmplx	result;

	result.real = z1.real + z2.real;
	result.i = z1.i + z2.i;
	return (result);
}

t_cmplx	square_cmplx(t_cmplx z)
{
	t_cmplx	result;

	result.real = (z.real * z.real) - (z.i * z.i);
	result.i = 2 * z.real * z.i;
	return (result);
}
