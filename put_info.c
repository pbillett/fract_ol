#include "fractol.h"

#include <stdio.h>

int		expose_hook(t_wind *w)
{
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	put_info(w);
	return (0);
}

static void			put_string(char *s, int l, int c, t_wind *w)
{
	mlx_string_put(w->mlx, w->win, 3 + c * 10, l * 20, 0xFFFFFF, s);
}

void				put_info(t_wind *w)
{
	int				rmargin;
	int				tmargin;

	rmargin =  (w->width/1.5)/10;
	tmargin =  ((w->height/2)/20) + 13;
	put_string("Fractal     :", 1, 1, w);
	put_string(w->p.fr.name, 1, 15, w);
	put_string("Width/Height:", 2, 1, w);
	put_string(ft_itoa((int)w->p.fr.x), 2, 15, w);
	put_string("/", 2, 20, w);
	put_string(ft_itoa((int)w->p.fr.y), 2, 22, w);
	put_string("Iterations  :", 3, 1, w);
	put_string(ft_itoa((int)w->p.fr.it_max), 3, 15, w);
	put_string("Zoom        :", 4, 1, w);
	put_string(ft_itoa(((int)w->p.fr.zoom)), 4, 15, w);
	put_string("Motion      :", 5, 1, w);
	put_string(ft_itoa(((int)w->p.fr.motion)), 5, 15, w);

	put_string("KEYS:", tmargin + 1, rmargin, w);
	put_string("Fractal type  : 1/2/3 (numpad)", tmargin + 3, rmargin, w);
	put_string("Zoom          : Mousewheel", tmargin + 4, rmargin, w);
	put_string("Pan           : Arrow key", tmargin + 5, rmargin, w);
	put_string("Iterations    : +/- (numpad)", tmargin + 6, rmargin, w);
	put_string("Presets Julia : 1/2/3/4/5 (keypad)", tmargin + 7, rmargin, w);
	put_string("Colors Shuffle: Tab", tmargin + 8, rmargin, w);
	put_string("Colors -/+    : EFV/RGB", tmargin + 9, rmargin, w);
	put_string("Colors Min/Max: WDC/THN", tmargin + 10, rmargin, w);
}
