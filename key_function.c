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

int			mouse_function(int button, int x, int y, t_wind *w)
{
	
	/*int		mem_x;
	int		mem_y;

	mem_x = 0;
	mem_y = 0;*/
	ft_putchar('\n');
	ft_putstr("button:");
	ft_putnbr(button);
	ft_putchar('\n');
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putnbr(y);
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
		if (w->p.view_mode == 2 || w->p.view_mode == 3)
		{
			//before_zoom(w);
			w->p.fr.zoomf += w->p.fr.zoominit/w->p.fr.zoomfactor; //We need to multiply by two
			printf("zoomf:%.2f\n", w->p.fr.zoomf);
			w->p.fr.it_max += 50;//And add 50 incrementation
			//after_zoom(w);
		}
		else
		{
			w->p.fr.it_max += 1; // to incremtente details

			// On récupere le déclage depuis le coin en haut à gauche
			/*mem_x = w->img.width / 2;
			mem_y = w->img.height / 2;
			// On applique le decalage depuis le coin en haut à gauche
			w->img.x -= mem_x;
			w->img.y -= mem_y;*/

			/*w->img.width *= 2;
			w->img.height *= 2;*/
		}
	}
	if (button == 5)
	{
		if (w->p.fr.zoom == 100)
			set_mandelbrot(w);
		else
		{
			//before_zoom(w);
			w->p.fr.zoomf -= w->p.fr.zoominit/w->p.fr.zoomfactor; //We need to multiply by two
			printf("zoomf:%.2f\n", w->p.fr.zoomf);
			if (w->p.view_mode == 2 || w->p.view_mode == 3)
				w->p.fr.it_max -= 50;//And add 50 incrementation
			else
			{
				w->p.fr.it_max -= 1;//And add 50 incrementation
				w->img.width /= 2;
				w->img.height /= 2;
			}
			//after_zoom(w);
		}
	}
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	//ft_putnbr(w->point.y);
	//ft_putnbr(w->point.y);
	//mlx_pixel_put(w->mlx, w->win, w->point.x, w->point.y, w->point.color);
	return (0);
}
