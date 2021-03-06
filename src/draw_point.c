/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:28:09 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/03 15:31:02 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int					get_bigger(int numb1, int numb2)
{
	if (numb1 > numb2)
		return (numb1);
	else
		return (numb2);
}

t_rgbcolor			get_inbetweencolorgradient(t_rgbcolor start, t_rgbcolor end,
		float percent)
{
	t_rgbcolor		col;

	if (end.r == get_bigger(end.r, start.r))
		col.r = (end.r - start.r) * percent + start.r;
	else
		col.r = (start.r - end.r) * percent + end.r;
	if (end.g == get_bigger(end.g, start.g))
		col.g = (end.g - start.g) * percent + start.g;
	else
		col.g = (start.g - end.g) * percent + end.g;
	if (end.b == get_bigger(end.b, start.b))
		col.b = (end.b - start.b) * percent + start.b;
	else
		col.b = (start.b - end.b) * percent + end.b;
	return (col);
}

t_rgbcolor			colorgrade(float percent, t_gradientcol mycolorgrade)
{
	t_rgbcolor		color;
	int				i;
	t_rgbcolor		startcol;
	t_rgbcolor		endcol;
	float			percofcolor;

	i = 0;
	while (i < mycolorgrade.nbofcolor)
	{
		if ((float)percent < (float)mycolorgrade.lstpos[i])
		{
			startcol = mycolorgrade.lstcol[i - 1];
			endcol = mycolorgrade.lstcol[i];
			percofcolor = (percent - mycolorgrade.lstpos[i - 1]) /
				(mycolorgrade.lstpos[i] - mycolorgrade.lstpos[i - 1]);
			color = get_inbetweencolorgradient(startcol, endcol, percofcolor);
			return (color);
		}
		i++;
	}
	color = mycolorgrade.lstcol[i - 1];
	return (color);
}

t_gradientcol		ultra_fractalgrade(t_wind *w)
{
	t_gradientcol	gcolor;

	gcolor.nbofcolor = 5;
	gcolor.lstpos = malloc(sizeof(float) * gcolor.nbofcolor);
	gcolor.lstcol = malloc(sizeof(t_rgbcolor) * gcolor.nbofcolor);
	gcolor.lstpos[0] = 0.0;
	gcolor.lstcol[0] = hexatorgb("0x000764");
	gcolor.lstpos[1] = 0.16;
	gcolor.lstcol[1] = hexatorgb("0x206BCB");
	gcolor.lstpos[2] = 0.42;
	gcolor.lstcol[2] = hexatorgb("0xEDFFFF");
	gcolor.lstpos[3] = 0.6425;
	gcolor.lstcol[3] = hexatorgb("0xFFAA00");
	gcolor.lstpos[4] = 0.8575;
	gcolor.lstcol[4] = hexatorgb("0x000096");
	w->p.fr.color = colorgrade(FG(i) / 100, gcolor);
	return (gcolor);
}

void				draw_point(t_wind *w, int x, int y, t_rgbcolor color)
{
	int				index;

	index = (x * w->img.bits_per_pixel / 8) + (y * w->img.size_line);
	w->img.pxl_ptr[index] = color.r;
	w->img.pxl_ptr[index + 1] = color.g;
	w->img.pxl_ptr[index + 2] = color.b;
}
