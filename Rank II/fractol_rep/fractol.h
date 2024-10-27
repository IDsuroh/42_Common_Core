/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:44:08 by suroh             #+#    #+#             */
/*   Updated: 2024/10/27 11:28:45 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdio.h>
# include <stdlib.h> //malloc free
# include <unistd.h> //write
# include <math.h>
# include <X11/X.h> //keyhooks
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <X11/Xatom.h>
# include "minilibx-linux/mlx.h"
# define ERRMSG_MAN "\n\tUsage: ./fractol [mandelbrot]\n\n"
# define ERRMSG_JUL "\n\tUsage: ./fractol [julia] [real] [i]\n\n"
# define WDT 800
# define HGT 800
# define COLOR_BLACK       0x000000  // RGB(0, 0, 0)
# define COLOR_WHITE       0xFFFFFF  // RGB(255, 255, 255)

//structs
//IMAGE struct for pixel buffer
typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		biperpix;
	int		endian;
	int		line_len;
}		t_img;

typedef struct s_fct
{
	char	*name;
	void	*mlx_con;
	void	*mlx_win;
	t_img	img;
	double	esc_val;
	double	sft_x;
	double	sft_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
	int		itr_def;
}		t_fct;

//complex values
typedef struct s_cmplx
{
	double	real;
	double	i;
}		t_cmplx;

//string utils
int		ft_strncmp(char *s1, char *s2, int n);
void	putstr_fd(char *s, int fd);
double	atodbl(char *s);

//init
void	fct_init(t_fct	*fct);

//render
void	fct_rdr(t_fct *fct);

//math utils
double	map(double i, double new_min, double new_max, double win_max);
t_cmplx	sum_cmplx(t_cmplx z1, t_cmplx z2);
t_cmplx	square_cmplx(t_cmplx z);

//events utils
int		keys(int keysym, t_fct *fct);
int		mouses(int button, int x, int y, t_fct *fct);

//exit
int		close_com(t_fct *fct);

#endif
