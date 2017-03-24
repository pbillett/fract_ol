#include "fractol.h"

static void		set_nbrcomplexandz(t_wind *w, int x, int y)
{
	int			mousecenter_x;
	int			mousecenter_y;

	mousecenter_x = w->width/2 - w->p.fr.mouse_x;
	mousecenter_y = w->height/2 - w->p.fr.mouse_y;
	if (ft_strcmp(w->p.fr.name, "julia") == 0)
	{
		// On fait varier la constante C de julia, en fonction de la position
		// x, et y de notre souris sur l'écran :
		// Je rset ma position de la souris avec un point 0,0,0 au centre de l'ecran
		w->p.fr.fra->c_r = ((float)mousecenter_y/(float)w->p.fr.img_y) * 2; //Cx =  0.3 valeur max
		w->p.fr.fra->c_i = ((float)mousecenter_x/(float)w->p.fr.img_x) * 2; // Cy = 0.02 valeur max
		w->p.fr.fra->z_r = x / w->p.fr.zoom + w->p.fr.fra->x1;
		w->p.fr.fra->z_i = y / w->p.fr.zoom + w->p.fr.fra->y1;
	}
	else if (ft_strcmp(w->p.fr.name, "mandelbrot") == 0)
	{
		w->p.fr.fra->c_r = x / w->p.fr.zoom_x + w->p.fr.fra->x1;
		w->p.fr.fra->c_i = y / w->p.fr.zoom_y + w->p.fr.fra->y1;
		w->p.fr.fra->z_r = 0 + w->p.fr.mouse_x;
		w->p.fr.fra->z_i = 0 + w->p.fr.mouse_y;
	}
}

void mydraw(t_wind *w, int x, int y, t_rgbcolor color, int i)
{
	int index;

	index = x * (w->img.bits_per_pixel / 8) + (y * w->img.size_line);
		if (i == w->p.fr.it_max)
		{
			w->img.pxl_ptr[index] = 0;
			w->img.pxl_ptr[index + 1] = 0;
			w->img.pxl_ptr[index + 2] = 0;
		}
		else
		{
			w->img.pxl_ptr[index] = i * color.b;
			w->img.pxl_ptr[index + 1] = i * color.g;
			w->img.pxl_ptr[index + 2] = i * color.r;
		}
}

int					fractal(t_wind *w)
{
	int				i;
//	t_gradientcol	gradecolor;
	t_rgbcolor		color;

	color.r = 257;
	color.g = 20;
	color.b = 210;
	printf("true zoom: %d\n", w->p.fr.zoom);
	printf("it_max: %d\n", w->p.fr.it_max);
	printf("x1: %f\n", w->p.fr.fra->x1);
	printf("x2: %f\n", w->p.fr.fra->x2);
	printf("y1: %f\n", w->p.fr.fra->y1);
	printf("y2: %f\n", w->p.fr.fra->y2);
	//w->p.fr.c_r = w->p.fr.x1 + w->p.fr.key_x; // set start to x min;
	w->p.fr.x = 0;
	while (w->p.fr.x < w->width)
	{
		//w->p.fr.c_i = w->p.fr.y1 + w->p.fr.key_y; // set start to y min;
		w->p.fr.y = 0;
		while (w->p.fr.y < w->height)
		{
			set_nbrcomplexandz(w, w->p.fr.x, w->p.fr.y);
			/*if (w->p.fr.zoom > 1)
			{
				printf("result of while cond c_r: %.2f\n", w->p.fr.fra->c_r);
				printf("result of while cond c_i: %.2f\n", w->p.fr.fra->c_i);
				printf("result of while cond z_r: %.2f\n", w->p.fr.fra->z_r);
				printf("result of while cond z_i: %.2f\n", w->p.fr.fra->z_i);
				printf("result of while cond: %.2f\n", ft_squared(w->p.fr.fra->z_r) + ft_squared(w->p.fr.fra->z_i));
			}*/
			i = 0;
			while ((ft_squared(w->p.fr.fra->z_r) + ft_squared(w->p.fr.fra->z_i)) < 4 && i < w->p.fr.it_max)
			{
				w->p.fr.fra->tmp = w->p.fr.fra->z_r;
				w->p.fr.fra->z_r = (ft_squared(w->p.fr.fra->z_r) - ft_squared(w->p.fr.fra->z_i)) + w->p.fr.fra->c_r;
				w->p.fr.fra->z_i = 2*w->p.fr.fra->tmp*w->p.fr.fra->z_i + w->p.fr.fra->c_i;
				//if (w->p.fr.zoom > 1)
					//ft_putnbr(i);
				i++;
				mydraw(w, w->p.fr.x, w->p.fr.y, color, i);
//					if (w->p.fr.colorset == 0) //first color mode (change with spacebar)
//						draw_pointf(w, w->p.fr.x, w->p.fr.y, mlx_get_color_value(w->mlx, i*255 / w->p.fr.it_max));
//					else
//					{
//						gradecolor = ultra_fractalgrade();
//						color = colorgrade(i/100, gradecolor);
//						draw_point(w, w->p.fr.x, w->p.fr.y, rgbtohexa(color));
//					}
			}
			w->p.fr.y++;
		}
		w->p.fr.x++;
	}
	//put_info(w);
	printf("the end\n");
	return (0);
}
