#include "fractol.h"

void		error_arg(void)
{
	ft_putstr("Usage <filename> [mandelbrot/julia/triangle_sierpinski]\n");
	exit(1);
}

void		error_malloc(void)
{
	write(1, "Malloc error\n", 13);
}
