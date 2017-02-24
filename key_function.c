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

	//We set the mouse value to able to zoom from current mouse point position
	w->p.fr.mouse_x = x;
	w->p.fr.mouse_y = y;

	printf("c_r: %f\n", w->p.fr.c_r);
	printf("c_i: %f\n", w->p.fr.c_i);
	printf("mouse_x: %d\n", w->p.fr.mouse_x);
	printf("mouse_y: %d\n", w->p.fr.mouse_y);
	double mouseRe = (double)w->p.fr.mouse_x / (w->width / (w->p.fr.x2 - w->p.fr.x1)) + w->p.fr.x1;
	double mouseIm = (double)w->p.fr.mouse_y / (w->height / (w->p.fr.y2 - w->p.fr.y1)) + w->p.fr.y1;
	printf("mouseRe: %f\n", mouseRe);
	printf("mouseRe: %f\n", mouseIm);

	if (button == 4)//Zoom molette
	{
		if (w->p.view_mode == 2 || w->p.view_mode == 3)
		{
			w->p.fr.zoomf += 10;
			// Zoom in(1.1 value)
			apply_zoom(&w->p.fr, mouseRe, mouseIm, w->p.fr.zoomf/100);
			printf("zoomf:%.2f\n", w->p.fr.zoomf);
			w->p.fr.it_max += 100;//And add 50 incrementation
		}
		else
		{
			w->p.fr.it_max += 1; // to incremtente details
		}
	}
	if (button == 5)
	{
		if (w->p.view_mode == 2 || w->p.view_mode == 3)
		{
			w->p.fr.zoomf -= 10;
			// Zoom out (0.9 value)
			apply_zoom(&w->p.fr, mouseRe, mouseIm, 100/w->p.fr.zoomf);
			printf("zoomf:%.2f\n", w->p.fr.zoomf);
			w->p.fr.it_max -= 100;//And add 50 incrementation
		}
		else
		{
			w->p.fr.it_max -= 1;//And add 50 incrementation
		}
	}
	mlx_destroy_image(w->mlx, w->img.ptr_img);
	create_new_img(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	return (0);
}
