
#include "fractol.h"

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
