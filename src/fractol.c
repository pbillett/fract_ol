/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:25:26 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/04 12:06:19 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_mandelbrot				*init_mandelbrot(void)
{
	t_mandelbrot			*m;

	m = (t_mandelbrot *)malloc(sizeof(t_mandelbrot));
	if (m == NULL)
		error_malloc();
	m->x1 = -2.1;
	m->x2 = 0.6;
	m->y1 = -1.2;
	m->y2 = 1.2;
	m->z_r = 0;
	m->z_i = 0;
	m->c_r = 0;
	m->c_i = 0;
	m->tmp = 0;
	return (m);
}

t_mandelbrot				*init_julia(void)
{
	t_mandelbrot			*j;

	j = (t_mandelbrot *)malloc(sizeof(t_mandelbrot));
	if (j == NULL)
		error_malloc();
	j->x1 = -2;
	j->x2 = 2;
	j->y1 = -2;
	j->y2 = 2;
	j->z_r = 0;
	j->z_i = 0;
	j->c_r = 0;
	j->c_i = 0;
	j->tmp = 0;
	return (j);
}

void						set_parameters(t_wind *w)
{
	w->width = WIDTH;
	w->height = HEIGHT;
	w->p.fr.hexa_bg = "0x000000";
	w->img.x = 0;
	w->img.y = 0;
	w->p.fr.x = 0;
	w->p.fr.y = 0;
	FG(mouse_x) = 0;
	FG(mouse_y) = 0;
	FG(zoomspeed) = ZOOMSPEED;
	w->p.fr.colorset = COLORSET;
	w->img.width = WIDTH;
	w->img.height = HEIGHT;
	FG(zoom) = ZOOM;
	w->p.fr.coeff = COEFF;
	w->p.fr.it_max = ITMAX;
	w->p.fr.triwidth = w->width;
	w->p.fr.triheight = w->height;
}

void						set_mode(t_wind *w, char *fracname)
{
	w->p.fr.fra = init_mandelbrot();
	w->p.fr.motion = 0;
	(FG(it_max) == 4) ? (FG(it_max) = ITMAX) : 0;
	if (ft_strcmp(fracname, "mandelbrot") == 0)
	{
		w->p.view_mode = 2;
		w->p.fr.fra = init_mandelbrot();
	}
	else if (ft_strcmp(fracname, "julia") == 0)
	{
		w->p.view_mode = 3;
		w->p.fr.motion = 1;
		w->p.fr.fra = init_julia();
	}
	else if (ft_strcmp(fracname, "triangle_sierpinski") == 0)
	{
		w->p.view_mode = 4;
		w->p.fr.it_max = 4;
	}
	else if (ft_strcmp(fracname, "burningship") == 0)
	{
		w->p.view_mode = 5;
		w->p.fr.fra = init_burning();
	}
	w->p.fr.name = fracname;
}

t_wind						fract_ol(char *fracname)
{
	t_wind					w;

	w = create_new_window(fracname, WIDTH, HEIGHT);
	reinit_fractal(&w, fracname);
	ft_randcolorrgb(&w);
	create_new_img(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	put_info(&w);
	return (w);
}
