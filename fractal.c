/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:13:07 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/12 12:10:59 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			set_nbrcomplexandz(t_wind *w, int x, int y)
{
	if (ft_strcmp(w->p.fr.name, "julia") == 0)
	{
		FF(c_r) = FG(mouse_xjul);
		FF(c_i) = FG(mouse_yjul);
		FF(z_r) = x / FG(zoom_x) + FF(x1);
		FF(z_i) = y / FG(zoom_y) + FF(y1);
	}
	else if (ft_strcmp(w->p.fr.name, "mandelbrot") == 0)
	{
		FF(c_r) = x / FG(zoom_x) + FF(x1);
		FF(c_i) = y / FG(zoom_y) + FF(y1);
		FF(z_r) = 0 + FG(mouse_x);
		FF(z_i) = 0 + FG(mouse_y);
	}
	else if (ft_strcmp(w->p.fr.name, "burningship") == 0)
	{
		FF(c_r) = x / FG(zoom_x) + FF(x1);
		FF(c_i) = y / FG(zoom_y) + FF(y1);
		FF(z_r) = 0;
		FF(z_i) = 0;
	}
}

void				mydraw(t_wind *w, int x, int y, t_rgbcolor color)
{
	int				index;

	index = x * (w->img.bits_per_pixel / 8) + (y * w->img.size_line);
	if (FG(i) == w->p.fr.it_max)
	{
		w->img.pxl_ptr[index] = 0;
		w->img.pxl_ptr[index + 1] = 0;
		w->img.pxl_ptr[index + 2] = 0;
	}
	else
	{
		w->img.pxl_ptr[index] = FG(i) * color.b;
		w->img.pxl_ptr[index + 1] = FG(i) * color.g;
		w->img.pxl_ptr[index + 2] = FG(i) * color.r;
	}
}

void				reinit_fractal(t_wind *w, char *fracname)
{
	set_parameters(w);
	set_mode(w, fracname);
	init_zoom(w);
}

static void			draw_fspacemode(t_wind *w)
{
	if (w->p.fr.colorset == 1)
	{
		if (FG(i) == FG(it_max))
			w->p.fr.color = (t_rgbcolor){0, 0, 0};
		else
			ultra_fractalgrade(w);
		draw_point(w, FG(x), FG(y), w->p.fr.color);
	}
	else if (ft_strcmp(w->p.fr.name, "burningship") == 0)
		mydraw(w, FG(x), FG(y), FG(color));
}

int					fractal(t_wind *w)
{
	FG(x) = 0;
	while (FG(x) < w->width)
	{
		FG(y) = 0;
		while (FG(y) < w->height)
		{
			set_nbrcomplexandz(w, FG(x), FG(y));
			FG(i) = 0;
			while ((ft_squared(FF(z_r)) + ft_squared(FF(z_i))) < 4 &&
					FG(i) < FG(it_max))
			{
				FF(tmp) = FF(z_r);
				set_zr_zi(w);
				FG(i)++;
				if (w->p.fr.colorset == 0 && !(ft_strcmp(w->p.fr.name,
								"burningship") == 0))
					mydraw(w, FG(x), FG(y), FG(color));
			}
			draw_fspacemode(w);
			FG(y)++;
		}
		FG(x)++;
	}
	return (0);
}
