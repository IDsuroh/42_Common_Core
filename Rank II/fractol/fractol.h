/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:44:08 by suroh             #+#    #+#             */
/*   Updated: 2024/10/27 11:11:29 by suroh            ###   ########.fr       */
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
# define COLOR_INDIGO      0x4B0082  // RGB(75, 0, 130)
# define COLOR_LIGHT_INDIGO 0x6A5ACD // RGB(106, 90, 205)
# define COLOR_DARK_INDIGO  0x3F007D // RGB(63, 0, 125)
# define COLOR_VIOLET      0x8A2BE2  // RGB(138, 43, 226)
# define COLOR_LAVENDER    0xE6E6FA  // RGB(230, 230, 250)
# define COLOR_NAVY        0x000080  // RGB(0, 0, 128)
# define COLOR_SILVER      0xC0C0C0  // RGB(192, 192, 192)
# define COLOR_SLATE_BLUE  0x6A5ACD  // RGB(106, 90, 205)
# define COLOR_SKY_BLUE         0x87CEEB  // RGB(135, 206, 235)
# define COLOR_DEEP_SKY_BLUE    0x00BFFF  // RGB(0, 191, 255)
# define COLOR_DODGER_BLUE      0x1E90FF  // RGB(30, 144, 255)
# define COLOR_CORNFLOWER_BLUE  0x6495ED  // RGB(100, 149, 237)
# define COLOR_MEDIUM_SLATE_BLUE 0x7B68EE  // RGB(123, 104, 238)
# define COLOR_STEEL_BLUE       0x4682B4  // RGB(70, 130, 180)
# define COLOR_LIGHT_STEEL_BLUE  0xB0E0E6  // RGB(176, 224, 230)
# define COLOR_ROYAL_BLUE       0x4169E1  // RGB(65, 105, 225)
# define COLOR_PERIWINKLE       0xCCCCFF  // RGB(204, 204, 255)
# define COLOR_ICE_BLUE         0xC9FFFF  // RGB(201, 255, 255)
# define COLOR_LIGHT_BLUE       0xADD8E6  // RGB(173, 216, 230)
# define COLOR_TEAL_BLUE        0x367588  // RGB(54, 117, 136)
# define COLOR_CYAN             0x00FFFF  // RGB(0, 255, 255)

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
