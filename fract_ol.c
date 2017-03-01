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
	// Position of Mouse by Default
	w->p.fr.mouse_x = 0;
	w->p.fr.mouse_y = 0;
	return (0);
}

static void		set_fracparameters(t_wind *w)
{
	w->p.fr.key_x = 0;// To move with keyboard key in fractal
	w->p.fr.key_y = 0;
	w->p.fr.zoomspeed = 50;// Zoom speed (Fast:70, Default:50, smooth Zoom:10 (but harder for calcultation),)
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
	// Mode para par défault (touche F2/F3/F4 pour changer)
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
	{
		ft_putstr("triangle sierpinski\n");
		w->p.view_mode = 4;
	}
	w->p.fr.name = fracname;
}

t_wind			fract_ol(char *fracname)
{
	t_wind		w;

	set_winsize(&w, fracname);
	w = create_new_window(fracname, w.width, w.height);
	set_mode(&w, fracname);
	set_parameters(&w);
	set_fracparameters(&w);
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
		ft_putstr("w->p.fr.name:\n");
		ft_putstr(lstwin[i].p.fr.name);
		ft_putstr("\n");

		ft_putstr("1\n");
		mlx_key_hook(lstwin[i].win, key_function, &(lstwin[i]));
		ft_putstr("2\n");
		mlx_mouse_hook(lstwin[i].win, mouse_function, &(lstwin[i]));
		ft_putstr("3\n");
		if ((lstwin[i]).p.view_mode == 3)
			mlx_hook(lstwin[i].win, MOTIONNOTIFY, POINTERMOTIONMASK, mouse_motion_function, &(lstwin[i]));
		mlx_expose_hook(lstwin[i].win, expose_hook, &(lstwin[i]));
		ft_putstr("4\n");
		i++;
	}
	i = 0;
	while (i < numbwind)
	{
		mlx_loop((lstwin[i]).mlx);
		i++;
	}
}
