#include "fractol.h"

static int			check_fractal_name(char *fracname)
{
	if ((ft_strcmp(fracname, "mandelbrot") == 0)
	|| (ft_strcmp(fracname, "julia") == 0)
	|| (ft_strcmp(fracname, "triangle_sierpinski") == 0))
		return (1);
	return (0);
}

int					main(int argc, char **argv)
{
	int				i;
	t_wind			*listwin;

	i = 0;
	listwin = malloc (sizeof(t_wind) * (argc - 1));
	while (i+1 < argc)
	{
		ft_putnbr(i+1);
		ft_putnbr(argc);
		if (!argv[i+1] || !check_fractal_name(argv[i+1]) || argc < 2)
		{
			ft_putendl("mandelbrot");
			ft_putendl("julia");
			ft_putendl("triangle_sierpinski");
			return (0);
		}
		i++;
	}
	i = 0;
	while ((i+1) < argc)
	{
		listwin[i] = fract_ol(argv[i+1]);
		i++;
	}
	start_hooks(listwin, argc - 1);
	return (0);
}
