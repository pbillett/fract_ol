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
	if (keycode == EXIT)
		exit(0);
	if (keycode == F2)//F2 Vue Isometrique
		w->p.view_mode = 2; // Mode iso par défault (touche F2/F3 pour changer)
	else if (keycode == F3)//F3 Vue Parallèle
		w->p.view_mode = 3; // Mode iso par défault (touche F2/F3 pour changer)
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	return (0);
}

int			mouse_function(int button, int x, int y, t_wind *w)
{
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
	if (button == 4)//Zoom molette
	{
		printf("c_r: %f\n", w->p.fr.c_r);
		printf("c_i: %f\n", w->p.fr.c_i);
		if (w->p.view_mode == 2 || w->p.view_mode == 3)
		{
			w->p.fr.zoomf += 0.1;
			w->p.fr.stepx = ((w->p.fr.x2 - w->p.fr.x1) * 100) / w->width;
			w->p.fr.stepy = ((w->p.fr.y2 - w->p.fr.y1) * 100) / w->height;
			printf("stepx: %.3f, stepy: %.3f\n", w->p.fr.stepx, w->p.fr.stepy);
			/*ft_putendl("1) decalage du curseur de la souris au centre:");
			w->p.fr.x1 = w->p.fr.x1 + ((((float)w->p.fr.mouse_x/w->p.fr.img_x) * w->p.fr.range_x) - (w->p.fr.range_x /2));
			w->p.fr.y1 = w->p.fr.y1 + ((((float)w->p.fr.mouse_y/w->p.fr.img_y) * w->p.fr.range_y) - (w->p.fr.range_y /2));
			w->p.fr.x2 = w->p.fr.x1 + w->p.fr.range_x;
			w->p.fr.y2 = w->p.fr.y1 + w->p.fr.range_y;*/
			//ft_refresh_view(w);
			//sleep(1);
			/*
			ft_putendl("2) zoom proportionnel par rapport au centre:");
			w->p.fr.zoomf += w->p.fr.zoominit/w->p.fr.zoomfactor; //We need to multiply by two
			w->p.fr.x1 = w->p.fr.x1 / 2;
			w->p.fr.y1 = w->p.fr.y1 / 2;
			w->p.fr.x2 = w->p.fr.x2 / 2;
			w->p.fr.y2 = w->p.fr.y2 / 2;
			w->p.fr.range_x = w->p.fr.x2 - w->p.fr.x1;
			w->p.fr.range_y = w->p.fr.y2 - w->p.fr.y1;*/
			//calc_imgsize(w);
			/*w->p.fr.x2 = w->p.fr.x2 / 2;
			w->p.fr.y2 = w->p.fr.y2 / 2;*/
			//ft_refresh_view(w);
			/*sleep(1);
			*/
			/*
			ft_putendl("3) decalage du centre sur le point de la souris:");
			w->p.fr.x1 = w->p.fr.x1 - ((((float)w->p.fr.mouse_x/w->p.fr.img_x) * w->p.fr.range_x) - (w->p.fr.range_x /2));
			w->p.fr.y1 = w->p.fr.y1 - ((((float)w->p.fr.mouse_y/w->p.fr.img_y) * w->p.fr.range_y) - (w->p.fr.range_y /2));
			printf("x1:: %.2f\n", w->p.fr.x1);
			printf("y1:: %.2f\n", w->p.fr.y1);
			w->p.fr.x2 = w->p.fr.x1 + w->p.fr.range_x;
			w->p.fr.y2 = w->p.fr.y1 + w->p.fr.range_y;*/
			//ft_refresh_view(w);
			//sleep(1);
			/*
			w->p.fr.x1 = w->p.fr.x1 / 2 + ((((float)w->p.fr.mouse_x/w->p.fr.img_x) * w->p.fr.range_x) - (w->p.fr.range_x/2));
			w->p.fr.y1 = w->p.fr.y1 / 2 + ((((float)w->p.fr.mouse_y/w->p.fr.img_y) * w->p.fr.range_y)/2);
			w->p.fr.x1 = w->p.fr.x2 / 2 + ((((float)w->p.fr.mouse_x/w->p.fr.img_x) * w->p.fr.range_x)/2);
			w->p.fr.y2 = w->p.fr.y2 / 2 - ((((float)w->p.fr.mouse_y/w->p.fr.img_y) * w->p.fr.range_y)/2);*/
			//w->p.fr.zoomf += w->p.fr.zoominit/w->p.fr.zoomfactor; //We need to multiply by two
			//before_zoom(w);
			printf("zoomf:%.2f\n", w->p.fr.zoomf);
			/*ft_putendl("zoomf: ");
			ft_putnbr((int)w->p.fr.zoomf);
			ft_putendl("\n");*/
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
			/*w->p.fr.x1 = (w->p.fr.x1 * 2);
			w->p.fr.y1 = (w->p.fr.y1 * 2);
			w->p.fr.x2 = (w->p.fr.x2 * 2);
			w->p.fr.y2 = (w->p.fr.y2 * 2);*/
			w->p.fr.zoomf -= 0.1; //We need to multiply by two
			//w->p.fr.zoomf -= w->p.fr.zoominit/w->p.fr.zoomfactor; //We need to multiply by two
			printf("zoomf:%.2f\n", w->p.fr.zoomf);
			/*ft_putendl("zoomf: ");
			ft_putnbr((int)w->p.fr.zoomf);
			ft_putendl("\n");*/
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
	return (0);
}
