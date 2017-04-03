/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_sierpinski.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:56:15 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/03 16:54:31 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>
#include <math.h>

#define OX 5
#define OY 5

static void			draw_trianglef(t_wind *w, t_triangle t, t_rgbcolor color)
{
	draw_2dline(w, t.dl, t.dr, color);
	draw_2dline(w, t.dr, t.dt, color);
	draw_2dline(w, t.dt, t.dl, color);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
}

static void			triangle_sierp_outside(t_wind *w, t_trisierp t)
{
	t_triangle		t1;

	t1.dl.x = t.x;
	t1.dl.y = t.y;
	t1.dl.z = 0;
	t1.dr.x = t.x + t.a;
	t1.dr.y = t.y;
	t1.dr.z = 0;
	t1.dt.x = t.x + (t.a / 2);
	t1.dt.y = (t.y + t.b);
	t1.dt.z = 0;
	draw_trianglef(w, t1, FG(color));
}

static void			triangle_sierp_inside(t_wind *w, t_trisierp t)
{
	t_triangle		t2;

	t2.dl.x = t.x + (t.a / 2);
	t2.dl.y = t.y;
	t2.dr.x = t.x + 3 * t.a / 4;
	t2.dr.y = t.y + t.b / 2;
	t2.dt.x = t.x + (t.a / 4);
	t2.dt.y = (t.y + t.b / 2);
	draw_trianglef(w, t2, FG(color));
}

static void			triangle_sierpinski(t_wind *w, t_trisierp t)
{
	t_trisierp		t1;
	t_trisierp		t2;
	t_trisierp		t3;

	t.b = -t.a * sqrt(3.0) / 2;
	if (t.n > 0)
	{
		triangle_sierp_outside(w, t);
		triangle_sierp_inside(w, t);
		t1 = t;
		t1.a = t.a / 2;
		t1.n = t.n - 1;
		triangle_sierpinski(w, t1);
		t2 = t;
		t2.x = t.x + t.a / 2;
		t2.a = t.a / 2;
		t2.n = t.n - 1;
		triangle_sierpinski(w, t2);
		t3 = t;
		t3.a = t.a / 2;
		t3.x = t.x + t.a / 4;
		t3.y = t.y + t.b / 2;
		t3.n = t.n - 1;
		triangle_sierpinski(w, t3);
	}
}

int					triangle_sierpinski_main(t_wind *w)
{
	t_trisierp		t;

	if (w->p.fr.it_max >= 4)
		t.n = w->p.fr.it_max / 4;
	else
		t.n = 1;
	t.x = 0;
	t.y = OY + w->p.fr.triheight;
	t.a = w->p.fr.triwidth;
	t.x = 0;
	triangle_sierpinski(w, t);
	return (0);
}
