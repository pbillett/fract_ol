

#include "fractol.h"

t_rgbcolor			ft_inttorgb(unsigned int n)
{
	t_rgbcolor		color;

	color.r = (n & 0xFF0000) >> 16;
	color.g = (n & 0xFF00) >> 8;
	color.b = (n & 0xFF);
	return (color);
}
