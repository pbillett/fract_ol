/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:31:52 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/12 11:57:09 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			init_zoom(t_wind *w)
{
	FG(zoom_x) = w->width / (FF(x2) - FF(x1));
	FG(zoom_y) = w->height / (FF(y2) - FF(y1));
}

void			ft_refresh_view(t_wind *w)
{
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	put_info(w);
}

int				mouse_motion_function(int x, int y, t_wind *w)
{
	if (w->p.fr.motion == 1)
	{
		w->p.fr.mouse_x = x;
		w->p.fr.mouse_y = y;
		FG(mouse_xjul) = (double)(w->height / 2 - FG(mouse_y)) /
			((double)w->width / 4);
		FG(mouse_yjul) = (double)(w->width / 2 - FG(mouse_x)) /
			((double)w->height / 4);
		ft_refresh_view(w);
	}
	return (0);
}

void			zoom(t_wind *w, int x, int y, int zoominbool)
{
	double		tx;
	double		ty;

	tx = x / FG(zoom_x) + FF(x1);
	ty = y / FG(zoom_y) + FF(y1);
	FF(x1) = tx - w->p.fr.coeff;
	FF(x2) = tx + w->p.fr.coeff;
	FF(y1) = ty - w->p.fr.coeff;
	FF(y2) = ty + w->p.fr.coeff;
	if (zoominbool)
		w->p.fr.it_max += 1;
	else
		w->p.fr.it_max -= 1;
	init_zoom(w);
}

int				mouse_function(int button, int x, int y, t_wind *w)
{
	if (button == 1)
	{
		if (w->p.fr.motion == 0)
			w->p.fr.motion = 1;
		else
			w->p.fr.motion = 0;
	}
	if (button == MOUSE_R)
		reinit_fractal(w, w->p.fr.name);
	if (button == 4)
	{
		FG(zoom)++;
		w->p.fr.coeff *= FG(zoomspeed);
		zoom(w, x, y, 1);
		w->p.fr.triwidth *= 1.1;
	}
	if (button == 5)
	{
		FG(zoom)--;
		w->p.fr.coeff /= FG(zoomspeed);
		zoom(w, x, y, 0);
		w->p.fr.triwidth /= 1.1;
	}
	ft_refresh_view(w);
	return (0);
}
