/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:53:11 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/12 12:08:36 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_mandelbrot				*init_burning(void)
{
	t_mandelbrot			*b;

	b = (t_mandelbrot *)malloc(sizeof(t_mandelbrot));
	if (b == NULL)
		error_malloc();
	b->x1 = -2.1;
	b->x2 = -2.5;
	b->y1 = 0.39;
	b->y2 = 0.5;
	b->z_r = 0;
	b->z_i = 0;
	b->c_r = 0;
	b->c_i = 0;
	b->tmp = 0;
	return (b);
}

void						set_zr_zi(t_wind *w)
{
	if (ft_strcmp(w->p.fr.name, "burningship") == 0)
	{
		FF(z_r) = ft_fabs(ft_squared(FF(z_r)) - ft_squared(FF(z_i))) + FF(c_r);
		FF(z_i) = ft_fabs(2 * FF(tmp) * FF(z_i)) + FF(c_i);
	}
	else
	{
		FF(z_r) = ft_squared(FF(z_r)) - ft_squared(FF(z_i)) + FF(c_r);
		FF(z_i) = 2 * FF(tmp) * FF(z_i) + FF(c_i);
	}
}
