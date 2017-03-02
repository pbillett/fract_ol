#include "fract_ol.h"

#define MOTIONNOTIFY		6
#define BUTTONMOTIONMASK	(1L<<13)
#define POINTERMOTIONMASK	(1L<<6)
#define NOEVENTMASK			0L

void		set_boundaries_imaginary(t_wind *w)
{
	w->p.fr.x1 = - (float)(w->img.width / 2) / 100;
	w->p.fr.x2 = (float)(w->img.width / 2) / 100;
	w->p.fr.y1 = - (float)(w->img.height / 2) / 100;
	w->p.fr.y2 = (float)(w->img.height / 2) / 100;
}

static void		set_parameters(t_wind *w)
{
	w->p.graphic_mode = 2; // Mode filaire par défault (touche nombre pour changer)
	w->p.fr.hexa_bg = "0x000000"; //Noir
	w->img.padh = 0; //Padding deplacement img par décalage fleche
	w->img.padv = 0;
	w->img.x = 0; //Position of image in window
	w->img.y = 0; // Position of Mouse by Default
	w->p.fr.mouse_x = 0;
	w->p.fr.mouse_y = 0;
	w->p.fr.key_x = 0;// To move with keyboard key in fractal
	w->p.fr.key_y = 0;
	w->p.fr.zoomspeed = 5;// Zoom speed (Fast:70, Default:50, smooth Zoom:10 (but harder for calcultation),)
	w->p.fr.colorset = 0;//set color set default: 0 - spacebar for change
	w->p.fr.quality_of_details = 70;// Quality of details of fractal (Default:50)
	if (w->p.view_mode == 2 || w->p.view_mode == 3)
	{
		w->img.width = 540;
		w->img.height = 480;
		set_boundaries_imaginary(w);
		w->p.fr.zoomf = 100;//Zoom et nbr iteration
		w->p.fr.it_max = 100;//Define at startup
		calc_imgsize(w);
	}
	else
	{
		w->img.width = 758;
		w->img.height = 655;
		w->p.fr.zoom = 1;//Zoom et nbr iteration
		w->p.fr.it_max = 1;//Define at startup
	}
}

static void			set_winsize(t_wind *w, char *fracname)
{
	if (ft_strcmp(fracname, "triangle_sierpinski") == 0)
	{
		w->width = 758;
		w->height = 655;
	}
	else
	{
		w->width = 540;
		w->height = 480;
	}
}

static void			set_mode(t_wind *w, char *fracname)
{
	if (ft_strcmp(fracname, "mandelbrot") == 0)
		w->p.view_mode = 2;
	else if (ft_strcmp(fracname, "julia") == 0)
		w->p.view_mode = 3;
	else if (ft_strcmp(fracname, "triangle_sierpinski") == 0)
		w->p.view_mode = 4;
	w->p.fr.name = fracname;
}

t_wind			fract_ol(char *fracname)
{
	t_wind		w;

	set_winsize(&w, fracname);
	w = create_new_window(fracname, w.width, w.height);
	set_mode(&w, fracname);
	set_parameters(&w);
	create_new_img(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	return (w);
}

void			start_hooks(t_wind *lstwin, int numbwind)
{
	int			i;

	i = 0;
	while (i < numbwind)
	{
		mlx_key_hook(lstwin[i].win, key_function, &(lstwin[i]));
		mlx_mouse_hook(lstwin[i].win, mouse_function, &(lstwin[i]));
		if ((lstwin[i]).p.view_mode == 3)
			mlx_hook(lstwin[i].win, MOTIONNOTIFY, POINTERMOTIONMASK, mouse_motion_function, &(lstwin[i]));
		mlx_expose_hook(lstwin[i].win, expose_hook, &(lstwin[i]));
		i++;
	}
	i = 0;
	while (i < numbwind)
	{
		mlx_loop((lstwin[i]).mlx);
		i++;
	}
}
