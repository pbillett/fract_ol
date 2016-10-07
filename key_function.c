#include "fract_ol.h"

int		expose_hook(t_wind *w)
{
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	return (0);
}

int		key_function(int keycode, t_wind *w)
{
	ft_putendl("Keyevent");
	ft_putnbr(keycode);
	ft_putchar('\n');
	// ECHAP (to quit)
	if (keycode == 65307)
		exit(0);
	// ROTATION:
	if (keycode == 65361 && w->img.x >= 0) // fleche gauche
	{
		w->p.rot.y -= 5;
		ft_putstr("roty:");
		ft_putnbr(w->p.rot.y);
		ft_putchar('\n');
	}
	else if (keycode == 65363 && w->img.x < w->width) // fleche droite
	{
		w->p.rot.y += 5;
		ft_putstr("roty:");
		ft_putnbr(w->p.rot.y);
		ft_putchar('\n');
	}
	else if (keycode == 65362 && w->img.y >= 0) // fleche haut
	{
		w->p.rot.x += 5;
		ft_putstr("rotx:");
		ft_putnbr(w->p.rot.x);
		ft_putchar('\n');
		//w->img.y += 5;
	}
	else if (keycode == 65364 && w->img.y < w->height) // fleche bas
	{
		w->p.rot.x -= 5;
		ft_putstr("rotx:");
		ft_putnbr(w->p.rot.x);
		ft_putchar('\n');
		//w->img.y -= 5;
	}
	// DEPLACEMENT LATERAL (pan) (Pavé numérique)
	if (keycode == 65431)//haut (pav num)
		w->img.y -= 10;
	else if (keycode == 65433)//bas (pav num)
		w->img.y += 10;
	else if (keycode == 65432)//droite (pav num)
		w->img.x += 10;
	else if (keycode == 65430)//gauche (pav num)
		w->img.x -= 10;
	// ZOOM:
	if (keycode == 65451)//plus (pav num)
	{
		w->p.size_square++;
		w->p.angle_projpara++;
	}
	if (keycode == 65453)//moins (pav num)
	{
		w->p.size_square--;
		w->p.angle_projpara--;
	}
	// ACCENTUATION (Hauteur du terrain)
	if (keycode == 65365)//page up
	{
		w->p.accentuation++;
		//ft_putnbr(w->p.accentuation);
	}
	if (keycode == 65366)//page down
	{
		w->p.accentuation--;
		//ft_putnbr(w->p.accentuation);
	}
	// GRAPHIC MODES: (touche 1 à zéro)
	if (keycode == 38)//1 poitille
	{
		ft_putendl("mode point");
		w->p.graphic_mode = 1;
	}
	else if (keycode == 233)//2 filaire (par default)
	{
		ft_putendl("mode filaire");
		w->p.graphic_mode = 2;
	}
	else if (keycode == 34)//3 triangulate
	{
		ft_putendl("mode triangulate");
		w->p.graphic_mode = 3;
	}
	else if (keycode == 39)//4 rempli
	{
		ft_putendl("mode fill");
		w->p.graphic_mode = 4;
	}
	else if (keycode == 105)// i pour afficher point
	{
		ft_putendl("point");
		if (w->p.dot == 1)
			w->p.dot = 0;
		else
			w->p.dot = 1;
	}
	// VUE
	if (keycode == 65471)//F2 Vue Isometrique
		w->p.view_mode = 2; // Mode iso par défault (touche F2/F3 pour changer)
	else if (keycode == 65472)//F3 Vue Parallèle
		w->p.view_mode = 3; // Mode iso par défault (touche F2/F3 pour changer)
	// COULEURS
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	return (0);
}

int		mouse_function(int button, int x, int y, t_wind *w)
{
	ft_putnbr(w->point.x);
	ft_putchar('\n');
	ft_putendl("button");
	ft_putnbr(button);
	ft_putchar('\n');
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putnbr(y);
	ft_putchar('\n');
	ft_putstr("zoom_x:");
	ft_putnbr(w->p.fr.zoom_x);
	ft_putchar('\n');
	ft_putstr("zoom_y:");
	ft_putnbr(w->p.fr.zoom_y);
	ft_putchar('\n');

	//We set the mouse value
	w->p.fr.mouse_x = x;
	w->p.fr.mouse_y = y;
	/*
	w->p.fr.x1 = x - w->p.fr.h;
	w->p.fr.x2 = x + w->p.fr.h;
	w->p.fr.y1 = y - w->p.fr.h;
	w->p.fr.y2 = y + w->p.fr.h;
	*/
	if (button == 4)//Zoom molette
	{
		//ft_putendl("haut");
		w->p.fr.zoom_x *= 1.2; //We need to multiply by two
		w->p.fr.zoom_y *= 1.2; //We need to multiply by two
		w->p.fr.it_max += 50;//And add 50 incrementation
		w->p.fr.h += 0.1;//coupe l'image zoome
	}
	if (button == 5)
	{
		//ft_putendl("bas");
		w->p.fr.zoom_x /= 1.2;
		w->p.fr.zoom_y /= 1.2;
		w->p.fr.it_max -= 50;
		w->p.fr.h -= 0.1;
	}
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	//ft_putnbr(w->point.y);
	//ft_putnbr(w->point.y);
	//mlx_pixel_put(w->mlx, w->win, w->point.x, w->point.y, w->point.color);
	return (0);
}
