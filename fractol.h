


#ifndef FRACT_OL_H

# define FRACT_OL_H
#include "libft/inc/libft.h"
#include "libft/inc/minilibx/mlx.h"
//#include "libft/inc/minilibx_struct.h"
#include "struct.h"
#include "keymacro.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h> // A supprimer !

#define MOTIONNOTIFY		6
#define BUTTONMOTIONMASK	(1L<<13)
#define POINTERMOTIONMASK	(1L<<6)
#define NOEVENTMASK			0L
#define WIDTH 800
#define HEIGHT 800
#define ZOOM 1
#define COEFF 0.78
#define ITMAX 100
#define QUALDETAILS 70
#define ZOOMSPEED 0.1
#define COLORSET 0


void			draw_pointf(t_wind *w, int x, int y, int z);
void			calc_imgsize(t_wind *w);
int				fractal(t_wind *w);
void			start_hooks(t_wind *lstwin, int numbwind);
t_wind			fract_ol(char *filename);
t_wind			create_new_window(char *title, int width, int height);
int				create_new_img(t_wind *w);
int				dot_in_window(t_wind *w, int x, int y);
t_point			matrice_rotation(t_point p, t_point angle, t_dpoint r_angle);
int				draw_line(t_wind *w, t_point point, t_point pointd, int boolean);
int				before_zoom(t_wind *w);
int				after_zoom(t_wind *w);
int				key_function(int keycode, t_wind *w);
int				mouse_function(int button, int x, int y, t_wind *w);
int				mouse_motion_function(int x, int y, t_wind *w);
int				expose_hook(t_wind *w);
t_point			matrice_rotation(t_point p, t_point angle, t_dpoint r_angle);
void			color_line(int num1, int num2, size_t *color);
void			draw_point(t_wind *w, int x, int y, char *hexacolor);
int				triangle_sierpinski_main(t_wind *w);
int				draw_2dline(t_wind *w, t_point p, t_point pd, char *hexacolor);
t_line			set_parameters_tline(t_line v);
t_line			convert_3ddot_to2dline(t_point p, t_point pd);
t_rgbcolor		hexatorgb(char *hexcolor);
void			ft_refresh_view(t_wind *w);
void			apply_zoom(t_mandelbrot *fr, double mouseRe, double mouseIm, double zoomFactor);
t_gradientcol	ultra_fractalgrade();
t_rgbcolor		colorgrade(float percent, t_gradientcol mycolorgrade);
char			*rgbtohexa(t_rgbcolor rgbcolor);
t_rgbcolor		ft_inttorgb(unsigned int n);

void			error_arg(void);
void			error_malloc(void);
void			put_info(t_wind *w);

#endif
