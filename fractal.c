#include "fractol.h"

// http://sdz.tdct.org/sdz/dessiner-la-fractale-de-mandelbrot.html
// https://www.codeproject.com/Articles/7513/Mandelbrot-Set-for-C

void		calc_imgsize(t_wind *w)
{
	w->p.fr.img_x = (w->p.fr.x2 - w->p.fr.x1) * (w->p.fr.zoomf);
	w->p.fr.img_y = (w->p.fr.y2 - w->p.fr.y1) * (w->p.fr.zoomf);
	printf("img_x calc: %d\n", w->p.fr.img_x);
	printf("img_y calc: %d\n", w->p.fr.img_y);
}

double interpolate(double start, double end, double interpolation)
{
    return start + ((end - start) * interpolation);
}

void apply_zoom(t_fractal *fr, double mouseRe, double mouseIm, double zoomFactor)
{
	double interpolation = 1.0 / zoomFactor;
	fr->x1 = interpolate(mouseRe, fr->x1, interpolation);
	fr->y1 = interpolate(mouseIm, fr->y1, interpolation);
	fr->x2 = interpolate(mouseRe, fr->x2, interpolation);
	fr->y2 = interpolate(mouseIm, fr->y2, interpolation);
}

static void		set_nbrcomplexandz(t_wind *w)
{
	int			mousecenter_x;
	int			mousecenter_y;

	if (ft_strcmp(w->p.fr.name, "julia") == 0)
	{
		//w->p.fr.c_r = 0.285;
		//w->p.fr.c_i = 0.01;

		// REF EXPLICATION CONSTANTE DE JULIA:
		// http://maths.wikidot.com/mandelbrot-et-julia
		// On fait varier la constante C de julia, en fonction de la position
		// x, et y de notre souris sur l'écran :
		// Je rset ma position de la souris avec un point 0,0,0 au centre de l'ecran
		mousecenter_x = w->width/2 - w->p.fr.mouse_x;
		mousecenter_y = w->height/2 - w->p.fr.mouse_y;

		w->p.fr.c_r = ((float)mousecenter_y/(float)w->p.fr.img_y) * 2; //Cx =  0.3 valeur max
		w->p.fr.c_i = ((float)mousecenter_x/(float)w->p.fr.img_x) * 2; // Cy = 0.02 valeur max
		//w->p.fr.z_r = w->p.fr.x/w->p.fr.zoomf + (w->p.fr.x1 - (w->p.fr.zoomfactor * w->p.fr.img_x));
		w->p.fr.z_r = w->p.fr.x/w->p.fr.zoomf + w->p.fr.x1;
		w->p.fr.z_i = w->p.fr.y/w->p.fr.zoomf + w->p.fr.y1;
	}
	else if (ft_strcmp(w->p.fr.name, "mandelbrot") == 0)
	{
		//https://github.com/Remaii/Fractol
		//http://stackoverflow.com/questions/41796832/smooth-zoom-with-mouse-in-mandelbrot-set-c?rq=1
		//http://stackoverflow.com/questions/14097559/zooming-in-on-mandelbrot-set-fractal-in-java
		//w->p.fr.c_r = (w->p.fr.x / w->p.fr.zoomf) + w->p.fr.x1;
		//w->p.fr.c_i = (w->p.fr.y / w->p.fr.zoomf) + w->p.fr.y1;
		w->p.fr.z_r = 0;
		w->p.fr.z_i = 0;
	}
}

int					fractal(t_wind *w)
{
	float			tmp;
	float			i;
	t_gradientcol	gradecolor;
	t_rgbcolor		color;

	gradecolor = ultra_fractalgrade();
	printf("x1: %f\n", w->p.fr.x1);
	printf("x2: %f\n", w->p.fr.x2);
	printf("y1: %f\n", w->p.fr.y1);
	printf("y2: %f\n", w->p.fr.y2);
	w->p.fr.intigralX = ((w->p.fr.x2 - w->p.fr.x1) / w->width);
	w->p.fr.intigralY = ((w->p.fr.y2 - w->p.fr.y1) / w->height);
	printf("intigralY: %f\n", w->p.fr.intigralY);
	printf("intigralX: %f\n", w->p.fr.intigralX);

	w->p.fr.c_r = w->p.fr.x1 + w->p.fr.key_x; // set start to x min;
	w->p.fr.x = 0;
	while (w->p.fr.x < w->width)
	{
		w->p.fr.c_i = w->p.fr.y1 + w->p.fr.key_y; // set start to y min;
		w->p.fr.y = 0; // set start to y min;
		while (w->p.fr.y < w->height)
		{
			set_nbrcomplexandz(w);
			i = 0;
			while ((ft_squared(w->p.fr.z_r) + ft_squared(w->p.fr.z_i)) < 4 && i < w->p.fr.it_max)
			{
				tmp = w->p.fr.z_r;
				w->p.fr.z_r = (ft_squared(w->p.fr.z_r) - ft_squared(w->p.fr.z_i)) + w->p.fr.c_r;
				w->p.fr.z_i = 2*tmp*w->p.fr.z_i + w->p.fr.c_i;
				i++;
			}
			if (i == w->p.fr.it_max)
				draw_pointf(w, w->p.fr.x, w->p.fr.y, 0x0000ff);
			else
			{
				if (w->p.fr.colorset == 0) //first color mode (change with spacebar)
					draw_pointf(w, w->p.fr.x, w->p.fr.y, mlx_get_color_value(w->mlx, i*255 / w->p.fr.it_max));
				else
				{
					color = colorgrade(i/100, gradecolor);
					draw_point(w, w->p.fr.x, w->p.fr.y, rgbtohexa(color));
				}
			}
			w->p.fr.y++;
			w->p.fr.c_i += w->p.fr.intigralY;
		}
		w->p.fr.x++;
		w->p.fr.c_r += w->p.fr.intigralX;
	}
	return (0);
}
