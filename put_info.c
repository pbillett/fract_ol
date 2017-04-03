#include "fractol.h"

int		expose_hook(t_wind *w)
{
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	put_info(w);
	return (0);
}

static void			put_string(char *s, int l, int c, t_wind *w)
{
	mlx_string_put(w->mlx, w->win, 3 + c * 10, l * 13, 0xFF0000, s);
}

void				put_info(t_wind *w)
{
	put_string("Fractal    :", 1, 0, w);
	put_string(w->p.fr.name, 1, 8, w);
	put_string("Width      :", 2, 0, w);
	put_string(ft_itoa((int)w->p.fr.x), 2, 8, w);
	put_string("Height     :", 3, 0, w);
	put_string(ft_itoa((int)w->p.fr.y), 3, 8, w);
	put_string("Iterations :", 4, 0, w);
	put_string(ft_itoa((int)w->p.fr.it_max), 4, 8, w);
	put_string("Zoom       :", 5, 0, w);
	put_string(ft_itoa(((int)w->p.fr.zoom)), 5, 8, w);
	put_string("Motion     :", 6, 0, w);
	put_string(ft_itoa(((int)w->p.fr.motion)), 6, 8, w);
}
