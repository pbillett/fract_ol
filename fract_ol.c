#include "fract_ol.h"

void		set_mandelbrot(t_wind *w)
{
	w->p.fr.name = "mandelbrot";
	w->p.fr.x1 = -2.1;
	w->p.fr.x2 = 0.6;
	w->p.fr.y1 = -1.2;
	w->p.fr.y2 = 1.2;
}

void		set_julia(t_wind *w)
{
	w->p.fr.name = "julia";
	w->p.fr.x1 = -1;
	w->p.fr.x2 = 1;
	w->p.fr.y1 = -1.2;
	w->p.fr.y2 = 1.2;
}

static int		set_parameters(t_wind *w)
{
	w->img.x_centerpoint = 500;
	w->img.y_centerpoint = 370;
	w->img.z_centerpoint = 370;
	// Parameters:
	w->p.graphic_mode = 2; // Mode filaire par défault (touche nombre pour changer)
	w->p.accentuation = 1;// On peut mettre une accentuation à 10 pour compenser les maps avec des petits chiffres ;). Default = 1

	w->p.rot.x = 0; // Rotation x par défault
	w->p.rot.y = 0; // Rotation x par défault
	w->p.rot.z = 0; // Rotation x par défault

	// Color Palette:
	w->p.color.hexa_top = "0xFFFFFF"; //Blanc
	w->p.color.hexa_mid = "0x024302"; //Vert
	w->p.color.hexa_bot = "0x432502"; //Marron
	w->p.color.hexa_axle = "0x9E11BF"; //Violet
	w->p.fr.hexa_bg = "0x000000"; //Noir

	// Definition des axes de rotation:
	w->r.p_x.x = 0;
	w->r.p_x.y = (w->height/2)-25;
	w->r.p_x.z = 0;
	w->r.pd_x.x = w->width;
	w->r.pd_x.y = (w->height/2)+25;
	w->r.pd_x.z = 0;

	w->r.p_y.x = w->width/2;
	w->r.p_y.y = (w->height/2)-25;
	w->r.p_y.z = 0;
	w->r.pd_y.x = w->width/2;
	w->r.pd_y.y = (w->height/2)+25;
	w->r.pd_y.z = 0;

	//Padding deplacement img par décalage fleche
	w->img.padh = 0;
	w->img.padv = 0;
	w->img.point.color = 0xFFFFFF;
	//Position of image in window
	w->img.x = 0;
	w->img.y = 0;
	return (0);
}

static void		set_fracparameters(t_wind *w)
{
	if (w->p.view_mode == 2 || w->p.view_mode == 3)
	{
		w->img.width = 270;
		w->img.height = 240;
		if (w->p.view_mode == 2)
			set_mandelbrot(w);
		else if (w->p.view_mode == 3)
			set_julia(w);
		w->p.fr.zoom = 100;//Zoom et nbr iteration
		w->p.fr.it_max = 50;//Define at startup
		w->p.fr.h = 0;//Define at startup
		calc_imgsize(w);
	}
	else
	{
		w->img.width = 758;
		w->img.height = 655;
	}
}

static void			set_winsize(t_wind *w, char *fracname)
{
	// Mode para par défault (touche F2/F3/F4 pour changer)
	if (ft_strcmp(fracname, "triangle sierpinski") == 0)
	{
		w->width = 758;
		w->height = 655;
	}
	else
	{
		w->width = 270;
		w->height = 240;
	}
}

static void			set_mode(t_wind *w, char *fracname)
{
	if (ft_strcmp(fracname, "mandelbrot") == 0)
		w->p.view_mode = 2;
	else if (ft_strcmp(fracname, "julia") == 0)
		w->p.view_mode = 3;
	else if (ft_strcmp(fracname, "triangle sierpinski") == 0)
		w->p.view_mode = 4;
}

int				fract_ol(char *fracname)
{
	t_wind		w;

	set_winsize(&w, fracname);
	w = create_new_window("fractal", w.width, w.height);
	set_mode(&w, fracname);
	set_parameters(&w);
	set_fracparameters(&w);
	create_new_img(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	mlx_key_hook(w.win, key_function, &w);
	mlx_expose_hook(w.win, expose_hook, &w);
	mlx_mouse_hook(w.win, mouse_function, &w);
	mlx_loop(w.mlx);
	return (0);
}
