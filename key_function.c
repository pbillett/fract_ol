#include "fractol.h"

void				ft_randcolorrgb(t_wind *w)
{
	FG(color.b) = rand() * 255;
	FG(color.g) = rand() * 255;
	FG(color.r) = rand() * 255;
}

static void			ft_colorkey(int keycode, t_wind *w)
{
	if (keycode == KEY_R)
		(FG(color.r) < 255) ? (FG(color.r)++) : 0;
	else if (keycode == KEY_G)
		(FG(color.g) < 255) ? (FG(color.g)++) : 0;
	else if (keycode == KEY_B)
		(FG(color.b) < 255) ? (FG(color.b)++) : 0;
	else if (keycode == KEY_E)
		(FG(color.r) > 0) ? (FG(color.r)--) : 0;
	else if (keycode == KEY_F)
		(FG(color.g) > 0) ? (FG(color.g)--) : 0;
	else if (keycode == KEY_V)
		(FG(color.b) > 0) ? (FG(color.b)--) : 0;
	else if (keycode == KEY_W)
		FG(color.r) = 0;
	else if (keycode == KEY_D)
		FG(color.g) = 0;
	else if (keycode == KEY_C)
		FG(color.b) = 0;
	else if (keycode == KEY_T)
		FG(color.r) = 255;
	else if (keycode == KEY_H)
		FG(color.g) = 255;
	else if (keycode == KEY_N)
		FG(color.b) = 255;
	else if (keycode == KEY_TAB)
		ft_randcolorrgb(w);
}

static void			ft_arrowkeys(int keycode, t_wind *w)
{
	if (keycode == L_ARROW)
	{
		FF(x1) -= FG(range_x) / 50;
		FF(x2) -= FG(range_x) / 50;
	}
	else if (keycode == R_ARROW)
	{
		FF(x1) += FG(range_x) / 50;
		FF(x2) += FG(range_x) / 50;
	}
	else if (keycode == U_ARROW)
	{
		FF(y1) -= FG(range_y) / 50;
		FF(y2) -= FG(range_y) / 50;
	}
	else if (keycode == D_ARROW)
	{
		FF(y1) += FG(range_y) / 50;
		FF(y2) += FG(range_y) / 50;
	}
}

static void			ft_page_space_zoom_keys(int keycode, t_wind *w)
{
	if (keycode == PAGE_U)
	{
		if (FG(zoomspeed) >= 0)
			FG(zoomspeed) -= 0.1;
	}
	else if (keycode == PAGE_D)
	{
		if (FG(zoomspeed) < 1.00)
		{
			if (FG(zoomspeed) < 0.8)
				FG(zoomspeed) += 0.1;
			else
				FG(zoomspeed) += 0.01;
		}
	}
	else if (keycode == SPACE)
	{
		if (w->p.fr.colorset == 0)
			w->p.fr.colorset = 1;
		else
			w->p.fr.colorset = 0;
	}
	else if (keycode == ZOOM_P)
		w->p.fr.it_max += 5;
	else if (keycode == ZOOM_M)
	{
		if(w->p.fr.it_max > 0)
			w->p.fr.it_max -= 5;
	}
}

int					key_function(int keycode, t_wind *w)
{
	if (keycode == EXIT)
		exit(0);
	if (keycode == F2)
	{
		w->p.fr.name = "mandelbrot";
		w->p.view_mode = 2; // Mode iso par défault (touche F2/F3 pour changer)
		w->p.fr.fra = init_mandelbrot();
	}
	else if (keycode == F3)
	{
		w->p.fr.name = "julia";
		w->p.view_mode = 3; // Mode iso par défault (touche F2/F3 pour changer)
		w->p.fr.fra = init_julia();
	}
	else if (keycode == F4)
	{
		w->p.view_mode = 4; // Mode iso par défault (touche F2/F3 pour changer)
		w->p.fr.name = "triangle_sierpinski";
	}
	FG(range_x) = FF(x2) - FF(x1);
	FG(range_y) = FF(y2) - FF(y1);
	ft_colorkey(keycode, w);
	ft_arrowkeys(keycode, w);
	julia_presetkeys(keycode, w);
	ft_page_space_zoom_keys(keycode, w);
	ft_refresh_view(w);
	return (0);
}
