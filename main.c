/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:11:27 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/03 18:11:45 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				start_hooks(t_wind *lstwin, int numbwind)
{
	int				i;

	i = 0;
	while (i < numbwind)
	{
		mlx_hook(lstwin[i].win, 2, 1, key_function, &(lstwin[i]));
		mlx_mouse_hook(lstwin[i].win, mouse_function, &(lstwin[i]));
		mlx_hook(lstwin[i].win, MOTIONNOTIFY, POINTERMOTIONMASK,
				mouse_motion_function, &(lstwin[i]));
		mlx_expose_hook(lstwin[i].win, expose_hook, &(lstwin[i]));
		i++;
	}
	i = 0;
	while (i < numbwind)
	{
		mlx_loop((lstwin[i]).mlx);
		i++;
	}
}

static int			check_fractal_name(char *fracname)
{
	if ((ft_strcmp(fracname, "mandelbrot") == 0)
	|| (ft_strcmp(fracname, "julia") == 0)
	|| (ft_strcmp(fracname, "triangle_sierpinski") == 0)
	|| (ft_strcmp(fracname, "burningship") == 0))
		return (1);
	return (0);
}

int					main(int argc, char **argv)
{
	int				i;
	t_wind			*listwin;

	i = 0;
	listwin = malloc(sizeof(t_wind) * (argc - 1));
	while (i + 1 < argc)
	{
		if (!argv[i + 1] || !check_fractal_name(argv[i + 1]) || argc < 2)
		{
			ft_putendl("mandelbrot");
			ft_putendl("julia");
			ft_putendl("triangle_sierpinski");
			ft_putendl("burningship");
			return (0);
		}
		i++;
	}
	i = 0;
	while ((i + 1) < argc)
	{
		listwin[i] = fract_ol(argv[i + 1]);
		i++;
	}
	start_hooks(listwin, argc - 1);
	return (0);
}
