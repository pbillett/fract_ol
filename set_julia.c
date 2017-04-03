/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_julia.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 19:30:20 by pbillett          #+#    #+#             */
/*   Updated: 2017/03/24 21:00:52 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		set_julia(t_wind *w, double c, double i)
{
	FG(mouse_xjul) = c;
	FG(mouse_yjul) = i;
	init_zoom(w);
}

void		julia_presetkeys(int keycode, t_wind *w)
{
	if (keycode == KEY_1)
		set_julia(w, -0.8, 0.2);
	if (keycode == KEY_2)
		set_julia(w, -0.8, 0);
	if (keycode == KEY_3)
		set_julia(w, 0.39, 0.2);
	if (keycode == KEY_4)
		set_julia(w, 0.39, 0.6);
	if (keycode == KEY_5)
		set_julia(w, -0.6, 0.6);
}
