/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:52:45 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/03 18:53:53 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					expose_hook(t_wind *w)
{
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	put_info(w);
	return (0);
}

static void			put_string(char *s, int l, int c, t_wind *w)
{
	mlx_string_put(w->mlx, w->win, 3 + c * 10, l * 20, 0xFFFFFF, s);
}

static void			put_info_mouse(t_wind *w)
{
	int				rmargin;
	int				tmargin;

	rmargin = (w->width / 1.5) / 10;
	tmargin = ((w->height / 2) / 20) + 17;
	put_string("MOUSE:", tmargin + 3, rmargin, w);
	put_string("Zoom               : Mousewheel", tmargin + 4, rmargin, w);
	put_string("Start/Pause motion : left click", tmargin + 5, rmargin, w);
	put_string("Reset fractal      : right click", tmargin + 6, rmargin, w);
}

static void			put_info_bottom(t_wind *w)
{
	int				rmargin;
	int				tmargin;

	rmargin = 1;
	tmargin = ((w->height / 2) / 20) + 13;
	put_string("KEYS:", tmargin + 3, rmargin, w);
	put_string("Fractal type  : 1/2/3 (numpad)", tmargin + 4, rmargin, w);
	put_string("Pan           : Arrow key", tmargin + 5, rmargin, w);
	put_string("Iterations    : +/- (numpad)", tmargin + 6, rmargin, w);
	put_string("Presets Julia : 1/2/3/4/5 (keypad)", tmargin + 7, rmargin, w);
	put_string("Colors Shuffle: Tab", tmargin + 8, rmargin, w);
	put_string("Colors -/+    : EFV/RGB", tmargin + 9, rmargin, w);
	put_string("Colors Min/Max: WDC/THN", tmargin + 10, rmargin, w);
}

void				put_info(t_wind *w)
{
	put_string("Fractal     :", 1, 1, w);
	put_string(w->p.fr.name, 1, 15, w);
	put_string("Width/Height:", 2, 1, w);
	put_string(ft_itoa((int)w->width), 2, 15, w);
	put_string("/", 2, 20, w);
	put_string(ft_itoa((int)w->height), 2, 22, w);
	put_string("Iterations  :", 3, 1, w);
	put_string(ft_itoa((int)w->p.fr.it_max), 3, 15, w);
	put_string("Zoom        :", 4, 1, w);
	put_string(ft_itoa(((int)w->p.fr.zoom)), 4, 15, w);
	put_string("Motion      :", 5, 1, w);
	put_string(ft_itoa(((int)w->p.fr.motion)), 5, 15, w);
	put_string("R :", 6, 1, w);
	put_string(ft_itoa(((int)FG(color.r))), 6, 5, w);
	put_string("G :", 7, 1, w);
	put_string(ft_itoa(((int)FG(color.g))), 7, 5, w);
	put_string("B :", 8, 1, w);
	put_string(ft_itoa(((int)FG(color.b))), 8, 5, w);
	put_info_bottom(w);
	put_info_mouse(w);
}
