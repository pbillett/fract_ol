#include "fractol.h"

static	t_mandelbrot		*init_mandelbrot()
{
	t_mandelbrot			*m;

	m = (t_mandelbrot *)malloc(sizeof(t_mandelbrot));
	if (m == NULL)
		error_malloc();
	m->x1 = -2.1;
	m->x2 = 0.6;
	m->y1 = -1.2;
	m->y2 = 1.2;
	m->z_r = 0;
	m->z_i = 0;
	m->c_r = 0;
	m->c_i = 0;
	m->tmp = 0;
	return (m);
}

static t_mandelbrot			*init_julia(void)
{
	t_mandelbrot			*j;

	j = (t_mandelbrot *)malloc(sizeof(t_mandelbrot));
	if (j == NULL)
		error_malloc();
	j->x1 = -2.1;
	j->x2 = 0.6;
	j->y1 = -1.2;
	j->y2 = 1.2;
	j->z_r = 0;
	j->z_i = 0;
	j->c_r = 0;
	j->c_i = 0;
	j->tmp = 0;
	return (j);
}

static void					set_parameters(t_wind *w)
{
	w->p.graphic_mode = 2; // Mode filaire par défault (touche nombre pour changer)
	w->p.fr.hexa_bg = "0x000000"; //Noir
	w->img.x = 0; //Position of image in window
	w->img.y = 0;
	w->p.fr.x = 0;
	w->p.fr.y = 0;
	w->p.fr.mouse_x = 0;
	w->p.fr.mouse_y = 0;
	w->p.fr.key_x = 0;// To move with keyboard key in fractal
	w->p.fr.key_y = 0;
	w->p.fr.zoomspeed = ZOOMSPEED;// Zoom speed (Fast:70, Default:50, smooth Zoom:10 (but harder for calcultation),)
	w->p.fr.colorset = COLORSET;//set color set default: 0 - spacebar for change
	w->p.fr.quality_of_details = QUALDETAILS;// Quality of details of fractal (Default:50)
	w->img.width = WIDTH;
	w->img.height = HEIGHT;
	w->p.fr.zoomf = ZOOMF;//Zoom et nbr iteration
	w->p.fr.it_max = ITMAX;//Define at startup
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

	w.width = WIDTH;
	w.height = HEIGHT;
	w = create_new_window(fracname, WIDTH, HEIGHT);
	set_parameters(&w);
	w.p.fr.mdb = init_mandelbrot();
	w.p.fr.jul = init_julia();
	set_mode(&w, fracname);
	if (ft_strcmp(w.p.fr.name, "mandelbrot") == 0)
		w.p.fr.fra = w.p.fr.mdb;
	if (ft_strcmp(w.p.fr.name, "julia") == 0)
		w.p.fr.fra = w.p.fr.jul;
	printf("w.p.fr.mdb.x2 start :%.2f\n", w.p.fr.mdb->x2);
	printf("w.p.fr.fra.x2 start :%.2f\n", w.p.fr.fra->x2);
	//calc_imgsize(&w);
	create_new_img(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	return (w);
}
