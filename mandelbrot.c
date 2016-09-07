#include "fract_ol.h"

int			mandelbrot(t_wind *w)
{
	int x;
	int y;
	// on définit la zone que l'on dessine. Ici, la fractale en entière
	double x1 = -2.1;
	double x2 = 0.6;
	double y1 = -1.2;
	double y2 = 1.2;
	int zoom = 100; // pour une distance de 1 sur le plan, on a 100 pixels sur l'image
	int iteration_max = 50;
	// on calcule la taille de l'image :
	int image_x = (x2 - x1) * zoom;
	int image_y = (y2 - y1) * zoom;
	double tmp;
	double c_r;
	double c_i;
	double z_r;
	double z_i;
	double i;
	
	ft_putnbr(w->img.size_line);
	ft_putchar('\n');
	ft_putnbr(w->img.octet_per_pixel);
	ft_putchar('\n');
	ft_putnbr(image_x);
	ft_putchar('\n');
	ft_putnbr(image_y);
	ft_putchar('\n');

	x = 0;
	while (x < image_x)
	{
		y = 0;
		while (y < image_y)
		{
			c_r = x/zoom + x1;
			c_i = y/zoom + y1;
			printf("c_r: %.2f\n", x/zoom + x1);
			printf("c_i: %.2f\n", y/zoom + y1);
			//sleep(5);
			z_r = 0;
			z_i = 0;
			i = 0;
			while (z_r*z_r + z_i*z_i < 4 && i < iteration_max)
			{
				tmp = z_r;
				z_r = z_r*z_r - z_i*z_i + c_r;
				z_i = 2*tmp*z_i + c_i;
				printf("tmp: %.2f\n", tmp);
				printf("z_r: %.2f\n", z_r);
				printf("z_i: %.2f\n", z_i);
				i++;
			}
			//dessiner pixel de coordonnées(x;y)
			if (i == iteration_max)
				mlx_pixel_put(w->mlx, w->win, x, y, 0x00FFFFFF);
			//*(w->img.pxl_ptr+(int)(y*(w->img.size_line))+(int)(x*(w->img.octet_per_pixel))) = (int)"0x00FFFFFF";
			y++;
		}
		x++;
	}
	return (0);
}
