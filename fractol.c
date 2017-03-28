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
	j->x1 = -2;
	j->x2 = 2;
	j->y1 = -2;
	j->y2 = 2;
	j->z_r = 0;
	j->z_i = 0;
	j->c_r = 0;
	j->c_i = 0;
	j->tmp = 0;
	return (j);
}

static void					set_parameters(t_wind *w)
{
	w->p.fr.hexa_bg = "0x000000";
	w->img.x = 0;
	w->img.y = 0;
	w->p.fr.x = 0;
	w->p.fr.y = 0;
	FG(mouse_x) = 0;
	FG(mouse_y) = 0;
	FG(color) = (t_rgbcolor){2, 20, 210};
	FG(zoomspeed) = ZOOMSPEED;// Zoom speed (Fast:70, Default:50, smooth Zoom:10 (but harder for calcultation),)
	w->p.fr.colorset = COLORSET;//set color set default: 0 - spacebar for change
	w->img.width = WIDTH;
	w->img.height = HEIGHT;
	FG(zoom) = ZOOM;//Zoom et nbr iteration
	w->p.fr.coeff = COEFF;
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

int					initlst_trisierp(t_wind *w, int nbrelem)
{
	int				i;
	t_lsttrisierp	*beginlst;

	i = 0;
	w->p.fr.lsttrisierp = malloc(sizeof(t_lsttrisierp) * nbrelem);
	beginlst = w->p.fr.lsttrisierp;
	while (i < nbrelem)
	{
		w->p.fr.lsttrisierp->data = malloc(sizeof(t_tri_sierp));
		i++;
		ft_putendl("init");
		w->p.fr.lsttrisierp = w->p.fr.lsttrisierp->next;
	}
	w->p.fr.lsttrisierp->data = NULL;
	w->p.fr.lsttrisierp = beginlst;
	ft_putendl("init end");
	return (0);
}

void				printlst_trisierp(t_wind *w)
{
	t_lsttrisierp	*beginlst;
	t_tri_sierp		*d;

	beginlst = w->p.fr.lsttrisierp;
	while (w->p.fr.lsttrisierp->next != NULL)
	{
		d = w->p.fr.lsttrisierp->data;
		triangle_sierpinski_main(w, d);
		w->p.fr.lsttrisierp = w->p.fr.lsttrisierp->next;
	}
	w->p.fr.lsttrisierp = beginlst;
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
	{
		w.p.fr.motion = 0; // Motion on julia
		w.p.fr.fra = w.p.fr.mdb;
	}
	if (ft_strcmp(w.p.fr.name, "julia") == 0)
	{
		w.p.fr.motion = 1; // Motion on julia
		w.p.fr.fra = w.p.fr.jul;
	}
	if (ft_strcmp(w.p.fr.name, "triangle_sierpinski") == 0)
	{
		initlst_trisierp(&w, 1);
		(*w.p.fr.lsttrisierp->data) = (t_tri_sierp){w.width/50, w.height/50, 1, 0};
		//w.p.fr.lsttrisierp = w.p.fr.lsttrisierp->next;
		//(*w.p.fr.lsttrisierp->data) = (t_tri_sierp){w.width/50, w.height/50, 1, 20};
		//w.p.fr.lsttrisierp = w.p.fr.lsttrisierp->next;
		/*w.p.fr.it_max = 1;
		w.p.fr.triwidth = w.width / 50; // 50 level of unzoom
		w.p.fr.triheight = w.height / 50;*/
	}
	init_zoom(&w);
	create_new_img(&w);
	put_info(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.ptr_img, w.img.x, w.img.y);
	return (w);
}
