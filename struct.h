/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:42:01 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/03 16:33:54 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct			s_rgbcolor
{
	int					r;
	int					g;
	int					b;
}						t_rgbcolor;

typedef struct			s_fractal
{
	int					i;
	char				*name;
	struct s_mandelbrot *fra;
	struct s_mandelbrot *mdb;
	struct s_mandelbrot *jul;
	float				x;
	float				y;
	int					colorset;
	t_rgbcolor			color;
	float				range_x;
	float				range_y;
	int					zoom;
	float				coeff;
	double				zoomspeed;
	float				quality_of_details;
	double				zoom_x;
	double				zoom_y;
	float				centerp_x;
	float				centerp_y;
	int					it_max;
	char				*hexa_bg;
	int					motion;
	double				mouse_x;
	double				mouse_y;
	double				mouse_xjul;
	double				mouse_yjul;
	double				triwidth;
	double				triheight;
}						t_fractal;

typedef struct			s_mandelbrot
{
	float				x1;
	float				x2;
	float				y1;
	float				y2;
	float				c_r;
	float				c_i;
	float				z_r;
	float				z_i;
	float				tmp;
}						t_mandelbrot;

typedef struct			s_trisierp
{
	double				x;
	double				y;
	double				a;
	double				b;
	unsigned long		n;
}						t_trisierp;

typedef struct			s_gradientcol
{
	int					nbofcolor;
	float				*lstpos;
	t_rgbcolor			*lstcol;
}						t_gradientcol;

typedef struct			s_colorpalette
{
	char				*hexa_bot;
	char				*hexa_mid;
	char				*hexa_top;
	char				*hexa_axle;
	t_rgbcolor			bot;
	t_rgbcolor			mid;
	t_rgbcolor			top;
	int					lowl;
	int					midl;
	int					topl;
	int					z;
	int					zd;
	int					min;
	int					max;
}						t_colorpalette;

typedef struct			s_line
{
	float				x;
	float				y;
	float				z;
	int					xdest;
	int					ydest;
	int					zdest;
	int					sign_x;
	int					sign_y;
	int					sign_z;
	float				bigdiff;
	float				diff_x;
	float				diff_y;
	float				diff_z;
	int					midx;
	int					midy;
}						t_line;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	size_t				color;
}						t_point;

typedef struct			s_triangle
{
	t_point				dl;
	t_point				dr;
	t_point				dt;
}						t_triangle;

typedef struct			s_img
{
	void				*ptr_img;
	int					x;
	int					y;
	int					start_x;
	int					start_y;
	int					width;
	int					height;
	int					padh;
	int					padv;
	int					x_centerpoint;
	int					y_centerpoint;
	int					z_centerpoint;
	char				*pxl_ptr;
	int					bits_per_pixel;
	int					size_line;
	int					octet_per_pixel;
	int					endian_type;
}						t_img;

typedef struct			s_params
{
	t_fractal			fr;
	int					view_mode;
}						t_params;

typedef struct			s_wind
{
	void				*mlx;
	void				*win;
	char				*title;
	int					width;
	int					height;
	t_point				point;
	t_img				img;
	t_params			p;
}						t_wind;

#endif
