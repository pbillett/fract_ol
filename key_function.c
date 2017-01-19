#include "fract_ol.h"

int		expose_hook(t_wind *w)
{
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
			before_zoom(w);
			w->p.fr.zoomf += w->p.fr.zoominit/w->p.fr.zoomfactor; //We need to multiply by two
			//printf("zoomf:%.2f\n", w->p.fr.zoomf);
			ft_putendl("zoomf: ");
			ft_putnbr((int)w->p.fr.zoomf);
			ft_putendl("\n");
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
			//printf("zoomf:%.2f\n", w->p.fr.zoomf);
			ft_putendl("zoomf: ");
			ft_putnbr((int)w->p.fr.zoomf);
			ft_putendl("\n");
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
