#include "fractol.h"

int		create_new_img(t_wind *w)
{
	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);
	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &w->img.size_line, &w->img.endian_type);
	w->img.octet_per_pixel = w->img.bits_per_pixel/8;
	if (w->p.view_mode == 2 || w->p.view_mode == 3)
		fractal(w);
	else if (w->p.view_mode == 4)
		triangle_sierpinski_main(w);
	return (0);
}

