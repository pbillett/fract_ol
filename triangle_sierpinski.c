#include "fractol.h"
#include <stdlib.h>
#include <math.h>

#define OX 5
#define OY 5

static void			draw_trianglef(t_wind *w, t_triangle t, t_rgbcolor color)
{
	draw_2dline(w, t.dl, t.dr, color);
	draw_2dline(w, t.dr, t.dt, color);
	draw_2dline(w, t.dt, t.dl, color);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
}

static void			triangle_sierp_outside(t_wind *w, double x, double y, double a)
{
	double			b;
	t_triangle		t;

	b = -a*sqrt(3.0)/2;
	t.dl.x = x;
	t.dl.y = y;
	t.dl.z = 0;
	t.dr.x = x + a;
	t.dr.y = y;
	t.dr.z = 0;
	t.dt.x = x + (a / 2);
	t.dt.y = (y + b);
	t.dt.z = 0;
	draw_trianglef(w, t, FG(color));
}

static void			triangle_sierp_inside(t_wind *w, double x, double y, double a)
{
	double			b;
	t_triangle		t2;

	b = -a*sqrt(3.0)/2;
	t2.dl.x = x + (a / 2);
	t2.dl.y = y;
	t2.dr.x = x + 3 * a / 4;
	t2.dr.y = y + b / 2;
	t2.dt.x = x + (a / 4);
	t2.dt.y = (y + b / 2);
	draw_trianglef(w, t2, FG(color));
}

static void			triangle_sierpinski(t_wind *w, double x, double y, double a, int n)
{
	double			b;

	b = -a*sqrt(3.0)/2;
	if (n>0)
	{
		triangle_sierp_outside(w, x, y, a);
		triangle_sierp_inside(w, x, y, a);
		triangle_sierpinski(w, x, y, a/2, n-1);
		triangle_sierpinski(w, x+a/2, y, a/2, n-1);
		triangle_sierpinski(w, x+a/4, y+b/2, a/2, n-1);
	}
}

int					triangle_sierpinski_main(t_wind *w)
{
	unsigned long	n;

	if (w->p.fr.it_max >= 4)
		n = w->p.fr.it_max / 4;
	else
		n = 1;
	triangle_sierpinski(w, 0, OY + w->p.fr.triheight, w->p.fr.triwidth, (int)n);
	return (0);
}
