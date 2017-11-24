/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 13:42:59 by pbillett          #+#    #+#             */
/*   Updated: 2017/03/24 20:54:06 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			dot_in_window(t_wind *w, int x, int y)
{
	if ((x > 0 && x < w->width) && (y > 0 && y < w->height))
		return (1);
	return (0);
}

int			draw_2dline(t_wind *w, t_point p, t_point pd, t_rgbcolor color)
{
	t_line	v;

	v = convert_3ddot_to2dline(p, pd);
	v = set_parameters_tline(v);
	while (rint(v.x) != v.xdest || rint(v.y) != v.ydest)
	{
		if (v.x != v.xdest)
			v.x += (v.sign_x * (v.diff_x / v.bigdiff));
		if (v.y != v.ydest)
			v.y += (v.sign_y * (v.diff_y / v.bigdiff));
		if (v.z != v.zdest)
			v.z += (v.sign_z * (v.diff_z / v.bigdiff));
		if (dot_in_window(w, rint(v.x), rint(v.y)) == 1)
			draw_point(w, rint(v.x), rint(v.y), color);
	}
	return (0);
}
