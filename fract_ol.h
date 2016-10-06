


#ifndef FRACT_OL

# define FRACT_OL
#include "libft/libft.h"
#include "minilibx/mlx.h"
#include "struct.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h> // A supprimer !

void		draw_point(t_wind *w, int x, int y, int z);
void		set_julia(t_wind *w);
void		set_mandelbrot(t_wind *w);
int			fractal(t_wind *w);
int			fract_ol(char *filename);
t_wind		create_new_window(char *title, int width, int height);
int			create_new_img(t_wind *w);
int			dot_in_window(t_wind *w, int x, int y);
t_point		matrice_rotation(t_point p, t_point angle, t_dpoint r_angle);
int			draw_line(t_wind *w, t_point point, t_point pointd, int boolean);
int			key_function(int keycode, t_wind *w);
int			mouse_function(int button, int x, int y, t_wind *w);
int			expose_hook(t_wind *w);
t_point		matrice_rotation(t_point p, t_point angle, t_dpoint r_angle);
void		color_line(int num1, int num2, size_t *color);

#endif
