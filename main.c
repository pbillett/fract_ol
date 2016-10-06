#include "fract_ol.h"

int					main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl("mandelbrot");
		ft_putendl("julia");
	}
	else
		fract_ol(argv[1]);
	return (0);
}
