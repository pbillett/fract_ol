#include "fract_ol.h"

int		create_new_img(t_wind *w)
{
	int x;
	x = 0;
	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);
	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &w->img.size_line, &w->img.endian_type);
	printf("bits_per_pixel: %d\nsize_line: %d\nendian_type: %d\n", w->img.bits_per_pixel, w->img.size_line, w->img.endian_type);
	w->img.octet_per_pixel = w->img.bits_per_pixel/8;

	while (x < 10)
	{
		mlx_pixel_put(w->mlx, w->win, x, 10, 0x00FFFFFF);
		x++;
	}
	if (w->p.view_mode == 2)
	{
		ft_putstr("julia");
		//julia(w);
	}
	else if (w->p.view_mode == 3)
	{
		ft_putstr("mandelbrot");
		mandelbrot(w);
	}
	return (0);
}

