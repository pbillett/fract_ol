#include "fract_ol.h"

int					main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl("mandelbrot");
		ft_putendl("julia");
		ft_putendl("triangle sierpinski");
		ft_putendl("carre sierpinski");
	}
	else
		fract_ol(argv[1]);
	return (0);
}
