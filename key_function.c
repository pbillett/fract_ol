#include "fractol.h"

int		expose_hook(t_wind *w)
{
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	return (0);
}

void				ft_colorkey(int keycode, t_wind *w)
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
}

void	ft_arrowkeys(int keycode, t_wind *w)
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

int		key_function(int keycode, t_wind *w)
{
	ft_putnbr(keycode);

	if (keycode == EXIT)
		exit(0);
	if (keycode == F2)//F2 Vue Isometrique
		w->p.view_mode = 2; // Mode iso par défault (touche F2/F3 pour changer)
	else if (keycode == F3)//F3 Vue Parallèle
		w->p.view_mode = 3; // Mode iso par défault (touche F2/F3 pour changer)
	FG(range_x) = FF(x2) - FF(x1);
	FG(range_y) = FF(y2) - FF(y1);
	ft_colorkey(keycode, w);
	ft_arrowkeys(keycode, w);
	julia_presetkeys(keycode, w);
	if (keycode == PAGE_U)
	{
		if (FG(zoomspeed) <= 10)
			FG(zoomspeed) += 1;
		printf("zoomspeed: %2.f\n", FG(zoomspeed));
	}
	else if (keycode == PAGE_D)
	{
		if (FG(zoomspeed) >= 0)
			FG(zoomspeed) -= 1;
		printf("zoomspeed: %2.f\n", FG(zoomspeed));
	}
	else if (keycode == SPACE)
	{
		if (w->p.fr.colorset == 0)
			w->p.fr.colorset = 1;
		else
			w->p.fr.colorset = 0;
	}
	else if (keycode == ZOOM_P)
		w->p.fr.it_max += 10;
	else if (keycode == ZOOM_M)
	{
		if(w->p.fr.it_max > 0)
			w->p.fr.it_max -= 10;
	}
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	return (0);
}

void			zoomin(t_wind *w, int x, int y)
{
	double		tx;
	double		ty;

	tx = x / FG(zoom_x) + FF(x1);
	ty = y / FG(zoom_y) + FF(y1);
	FF(x1) = tx - w->p.fr.coeff;
	FF(x2) = tx + w->p.fr.coeff;
	FF(y1) = ty - w->p.fr.coeff;
	FF(y2) = ty + w->p.fr.coeff;
	w->p.fr.it_max -= 5;
	FG(zoom_x) = w->width / (FF(x2) - FF(x1));
	FG(zoom_y) = w->height / (FF(y2) - FF(y1));
}

void			zoomout(t_wind *w, int x, int y)
{
	double		tx;
	double		ty;

	tx = x / FG(zoom_x) + FF(x1);
	ty = y / FG(zoom_y) + FF(y1);
	FF(x1) = tx - w->p.fr.coeff;
	FF(x2) = tx + w->p.fr.coeff;
	FF(y1) = ty - w->p.fr.coeff;
	FF(y2) = ty + w->p.fr.coeff;
	w->p.fr.it_max += 5;
	FG(zoom_x) = w->width / (FF(x2) - FF(x1));
	FG(zoom_y) = w->height / (FF(y2) - FF(y1));
}


int			mouse_function(int button, int x, int y, t_wind *w)
{
	if (button == 1) // Si click gauche
	{
		if (w->p.fr.motion == 0) // We set mouse_x active to activate mouse for julia
			w->p.fr.motion = 1;
		else
			w->p.fr.motion = 0;
	}
	if (button == 4)//Zoom molette
	{
		if (w->p.view_mode == 2 || w->p.view_mode == 3)
		{
			FG(zoom)++;
			w->p.fr.coeff *= FG(zoomspeed);
			zoomout(w, x, y);
			// Zoom in(1.1 value)
			//apply_zoom((w->p.fr.fra), mouseRe, mouseIm, FG(zoom)f/100);
			printf("zoom:%d\n", FG(zoom));
			printf("coeff:%.2f\n", w->p.fr.coeff);
			printf("w.p.fr.zoom_x :%.2f\n", FG(zoom_x));
			printf("w.p.fr.zoom_y :%.2f\n", FG(zoom_y));
			//w->p.fr.it_max += w->p.fr.quality_of_details;//And add 50 incrementation
		}
		else
		{
			if (w->p.fr.it_max != 6)
				w->p.fr.it_max += 1; // to incremtente details
		}
	}
	if (button == 5)
	{
		if (w->p.view_mode == 2 || w->p.view_mode == 3)
		{
			FG(zoom)--;
			w->p.fr.coeff /= FG(zoomspeed);
			zoomin(w, x, y);
			// Zoom out (0.9 value)
			//apply_zoom(w->p.fr.fra, mouseRe, mouseIm, 100/FG(zoom)f);
			printf("zoom:%d\n", FG(zoom));
			printf("coeff:%.2f\n", w->p.fr.coeff);
			printf("w.p.fr.zoom_x :%.2f\n", FG(zoom_x));
			printf("w.p.fr.zoom_y :%.2f\n", FG(zoom_y));
			//w->p.fr.it_max -= w->p.fr.quality_of_details;
		}
		else
		{
			if (w->p.fr.it_max > 0)
				w->p.fr.it_max -= 1;//And add 50 incrementation
		}
	}
	//ft_putnbr(button);
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	return (0);
}
