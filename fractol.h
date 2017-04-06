/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:40:00 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/04 12:06:46 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H
# include "libft/inc/libft.h"
# if MACROKEY == 1
# include "minilibx_macos/mlx.h"
# else
# include "minilibx/mlx.h"
# endif
# include "struct.h"
# include "keymacro.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define MOTIONNOTIFY		6
# define BUTTONMOTIONMASK	(1L<<13)
# define POINTERMOTIONMASK	(1L<<6)
# define NOEVENTMASK			0L
# define WIDTH 500
# define HEIGHT 500
# define ZOOM 1
# define COEFF 0.78
# define ITMAX 20
# define ZOOMSPEED 0.5
# define COLORSET 0
# define FF(x) w->p.fr.fra->x
# define FG(x) w->p.fr.x

char			*rgbtohexa(t_rgbcolor rgbcolor);
t_rgbcolor		hexatorgb(char *hexcolor);
void			start_hooks(t_wind *lstwin, int numbwind);
t_wind			fract_ol(char *filename);
int				fractal(t_wind *w);
t_wind			create_new_window(char *title, int width, int height);
int				create_new_img(t_wind *w);
int				key_function(int keycode, t_wind *w);
int				mouse_function(int button, int x, int y, t_wind *w);
int				mouse_motion_function(int x, int y, t_wind *w);
int				expose_hook(t_wind *w);
void			draw_point(t_wind *w, int x, int y, t_rgbcolor color);
void			draw_pointf(t_wind *w, int x, int y, int z);
int				dot_in_window(t_wind *w, int x, int y);
int				draw_line(t_wind *w, t_point point, t_point pointd,
		int boolean);
void			init_zoom(t_wind *w);
t_gradientcol	ultra_fractalgrade();
t_rgbcolor		colorgrade(float percent, t_gradientcol mycolorgrade);
void			julia_presetkeys(int keycode, t_wind *w);
int				triangle_sierpinski_main(t_wind *w);
int				draw_2dline(t_wind *w, t_point p, t_point pd, t_rgbcolor color);
t_line			set_parameters_tline(t_line v);
t_line			convert_3ddot_to2dline(t_point p, t_point pd);
void			ft_randcolorrgb(t_wind *w);
void			ft_refresh_view(t_wind *w);
void			put_info(t_wind *w);
void			error_malloc(void);
t_mandelbrot	*init_mandelbrot(void);
t_mandelbrot	*init_julia(void);
void			set_mode(t_wind *w, char *fracname);
void			set_parameters(t_wind *w);
void			reinit_fractal(t_wind *w, char *fracname);

#endif
