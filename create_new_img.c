#include "fract_ol.h"

int		create_new_img(t_wind *w)
{
	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);
	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &w->img.size_line, &w->img.endian_type);
	printf("bits_per_pixel: %d\nsize_line: %d\nendian_type: %d\n", w->img.bits_per_pixel, w->img.size_line, w->img.endian_type);
	w->img.octet_per_pixel = w->img.bits_per_pixel/8;
	if (w->p.view_mode == 2)
	{
		ft_putstr("julia");
		w->p.fr.name = "julia";
		set_julia(w);
	}
	else if (w->p.view_mode == 3)
	{
		ft_putstr("mandelbrot");
		w->p.fr.name = "mandelbrot";
		set_mandelbrot(w);
	}
	fractal(w);
	return (0);
}

