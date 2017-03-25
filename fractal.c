#include "fractol.h"

static void		set_nbrcomplexandz(t_wind *w, int x, int y)
{
	if (ft_strcmp(w->p.fr.name, "julia") == 0)
	{
		FF(c_r) = FG(mouse_xjul);
		FF(c_i) = FG(mouse_yjul);
		FF(z_r) = x / FG(zoom_x) + FF(x1);
		FF(z_i) = y / FG(zoom_y) + FF(y1);
	}
	else if (ft_strcmp(w->p.fr.name, "mandelbrot") == 0)
	{
		FF(c_r) = x / FG(zoom_x) + FF(x1);
		FF(c_i) = y / FG(zoom_y) + FF(y1);
		FF(z_r) = 0 + FG(mouse_x);
		FF(z_i) = 0 + FG(mouse_y);
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
	t_gradientcol	gradecolor;

	/*printf("true zoom: %d\n", FG(zoom));
	printf("color: r:%d, g:%d, b: %d\n", FG(color.r), FG(color.g), FG(color.b));
	printf("it_max: %d\n", w->p.fr.it_max);
	printf("x1: %f\n", FF(x1));
	printf("x2: %f\n", FF(x2));
	printf("y1: %f\n", FF(y1));
	printf("y2: %f\n", FF(y2));*/
	FG(x) = 0;
	while (FG(x) < w->width)
	{
		FG(y) = 0;
		while (FG(y) < w->height)
		{
			set_nbrcomplexandz(w, FG(x), FG(y));
			i = 0;
			while ((ft_squared(FF(z_r)) + ft_squared(FF(z_i))) < 4 && i < FG(it_max))
			{
				FF(tmp) = FF(z_r);
				FF(z_r) = (ft_squared(FF(z_r)) - ft_squared(FF(z_i))) + FF(c_r);
				FF(z_i) = 2 * FF(tmp) * FF(z_i) + FF(c_i);
				i++;
				if (w->p.fr.colorset == 0)
					mydraw(w, FG(x), FG(y), FG(color), i);
			}
			if (w->p.fr.colorset == 1)
			{
				gradecolor = ultra_fractalgrade();
				w->p.fr.color = colorgrade(i/100, gradecolor);
				draw_point(w, FG(x), FG(y), rgbtohexa(w->p.fr.color));
			}
			FG(y)++;
		}
		FG(x)++;
	}
	//ft_putstr("render");
	return (0);
}
