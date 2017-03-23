#include "fractol.h"

static void			put_string(char *s, int l, int c, t_wind *w)
{
	mlx_string_put(w->mlx, w->win, 3 + c * 10, l * 13, 0xFF0000, s);
}

void				put_info(t_wind *w)
{
	put_string("DEEP :", 0, 0, w);
	put_string(ft_itoa(w->p.fr.it_max), 0, 7, w);
	put_string("X    :", 1, 0, w);
	put_string(ft_itoa(w->p.fr.x), 1, 7, w);
	put_string("Y    :", 2, 0, w);
	put_string(ft_itoa(w->p.fr.y), 2, 7, w);
	put_string("Z    :", 3, 0, w);
	put_string(ft_itoa(w->p.fr.zoom), 3, 7, w);
	/*
	put_string("OPT_X:", 4, 0, w);
	put_string(ft_itoa(w->option_x), 4, 7, w);
	put_string("OPT_Y:", 5, 0, w);
	put_string(ft_itoa(w->option_y), 5, 7, w);*/
}
