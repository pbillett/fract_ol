#include "fractol.h"

int		create_new_img(t_wind *w)
{
	w->img.ptr_img = mlx_new_image(w->mlx, w->img.width, w->img.height);
	w->img.pxl_ptr = mlx_get_data_addr(w->img.ptr_img, &w->img.bits_per_pixel, &w->img.size_line, &w->img.endian_type);
	//printf("bits_per_pixel: %d\nsize_line: %d\nendian_type: %d\n", w->img.bits_per_pixel, w->img.size_line, w->img.endian_type);
	w->img.octet_per_pixel = w->img.bits_per_pixel/8;
	/*ft_putendl("create_new_img func");
	ft_putnbr(w->p.view_mode);
	ft_putstr("\n");*/
	if (w->p.view_mode == 2 || w->p.view_mode == 3)
	{
		//ft_putendl("julia or mandelbrot");
		fractal(w);
		put_info(w);
	}
	else if (w->p.view_mode == 4)
	{
		//ft_putendl("triangle_sierpinski_main");
		printlst_trisierp(w);
	}
	return (0);
}

