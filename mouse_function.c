/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 15:31:52 by pbillett          #+#    #+#             */
/*   Updated: 2016/12/27 15:37:43 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
/*
void		pencil(t_wind *w, int x, int y)
{
	int		i;
	int		j;
	int		brushsize;

	brushsize = 1;
	i = x - brushsize;
	while (i != (x + brushsize))
	{
		j = y - brushsize;
		while (j != (y + brushsize))
		{
			if (dot_in_window(w, i, j))
				draw_point(w, i, j, "0xFFFFFF");
			j++;
		}
		i++;
	}
}

int			mousepress_function(int button, int x, int y, t_wind *w)
{
	w->p.m.memm_x = x;
	w->p.m.memm_y = y;
	if (button == 1)
	{
		w->p.m.button1 = 1;
		w->p.m.mem_rotz = w->p.rot.z;
		w->p.m.mem_rotx = w->p.rot.x;
		w->p.m.mem_posx = w->p.t.x;
		w->p.m.mem_posy = w->p.t.y;
		w->p.m.mem_gizx = w->obj.gizt.t.x;
		w->p.m.mem_gizy = w->obj.gizt.t.y;
	}
	else if (button == 2)
	{
		w->p.m.button2 = 1;
		w->p.m.mem_spacing_x = w->p.x_spacing;
		w->p.m.mem_zaccentuation = w->p.zaccentuation;
	}
	else if (button == 3)
		w->p.m.button3 = 1;
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	help(w);
	return (0);
}

int			mouse_release_function(int button, int x, int y, t_wind *w)
{
	w->p.m.mem_posx = x;
	w->p.m.mem_posy = y;
	if (button == 1)
		w->p.m.button1 = 0;
	else if (button == 2)
		w->p.m.button2 = 0;
	else if (button == 3)
		w->p.m.button3 = 0;
	return (0);
}

static void	fc_bt1_mousemove(int x, int y, t_wind *w)
{
	int		transl_sens;

	transl_sens = 1000;
	if (w->p.space_mousemove == 1)
	{
		w->p.t.x = w->p.m.mem_posx + (int)(((float)(x - w->p.m.memm_x) /
		(float)w->img.width) * (float)transl_sens);
		w->p.t.y = w->p.m.mem_posy + (int)(((float)(y - w->p.m.memm_y) /
		(float)w->img.height) * (float)transl_sens);
		w->obj.gizt.t.x = w->p.m.mem_gizx + (int)(((float)(x - w->p.m.memm_x) /
		(float)w->img.width) * (float)transl_sens);
		w->obj.gizt.t.y = w->p.m.mem_gizy + (int)(((float)(y - w->p.m.memm_y) /
		(float)w->img.height) * (float)transl_sens);
	}
	else
	{
		w->p.rot.z = w->p.m.mem_rotz - (int)(((float)(x - w->p.m.memm_x) /
		(float)w->img.width) * (float)360);
		w->p.rot.x = w->p.m.mem_rotx - (int)(((float)(y - w->p.m.memm_y) /
		(float)w->img.height) * (float)360);
	}
}
i*/
int			mouse_motion_function(int x, int y, t_wind *w)
{
	//static int		prev_mouse_x;
	//static int		prev_mouse_y;

	//ft_putstr("before\n");
	//if (w->p.fr.mouse_x != x || w->p.fr.mouse_y != y)
	//{
	w->p.fr.mouse_x = x;
	w->p.fr.mouse_y = y;


	mlx_destroy_image(w->mlx, w->img.ptr_img);
	//ft_putstr("mid\n");
	create_new_img(w);
	//fractal(w);
	//ft_putstr("next\n");
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	//ft_putstr("end\n");
	return (0);
}
