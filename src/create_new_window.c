/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:32:18 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/03 15:32:25 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_wind			create_new_window(char *title, int width, int height)
{
	t_wind			w;

	w.mlx = mlx_init();
	w.width = width;
	w.height = height;
	w.title = title;
	w.win = mlx_new_window(w.mlx, w.width, w.height, w.title);
	return (w);
}
