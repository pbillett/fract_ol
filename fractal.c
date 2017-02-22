#include "fract_ol.h"

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

void applyZoom(t_fractal* e, double mouseRe, double mouseIm, double zoomFactor)
{
	double interpolation = 1.0 / zoomFactor;
	e->Re.min = interpolate(mouseRe, e->Re.min, interpolation);
	e->Im.min = interpolate(mouseIm, e->Im.min, interpolation);
	e->Re.max = interpolate(mouseRe, e->Re.max, interpolation);
	e->Im.max = interpolate(mouseIm, e->Im.max, interpolation);
}

static void		set_nbrcomplexandz(t_wind *w)
{
	if (ft_strcmp(w->p.fr.name, "julia") == 0)
	{
		//w->p.fr.c_r = 0.285;
		//w->p.fr.c_i = 0.01;

		// REF EXPLICATION CONSTANTE DE JULIA:
		// http://maths.wikidot.com/mandelbrot-et-julia
		// On fait varier la constante C de julia, en fonction de la position
		// x, et y de notre souris sur l'écran :
		w->p.fr.c_r = ((float)w->p.fr.mouse_y/(float)w->p.fr.img_y) * 0.5; //Cx =  0.3 valeur max
		w->p.fr.c_i = ((float)w->p.fr.mouse_x/(float)w->p.fr.img_x) * 0.02; // Cy = 0.02 valeur max
		//w->p.fr.z_r = w->p.fr.x/w->p.fr.zoomf + (w->p.fr.x1 - (w->p.fr.zoomfactor * w->p.fr.img_x));
		w->p.fr.z_r = w->p.fr.x/(w->p.fr.zoomf * 100) + w->p.fr.x1;
		w->p.fr.z_i = w->p.fr.y/(w->p.fr.zoomf * 100) + w->p.fr.y1;
	}
	else if (ft_strcmp(w->p.fr.name, "mandelbrot") == 0)
	{
		//w->p.fr.c_r = w->p.fr.x/w->p.fr.zoomf + w->p.fr.x1 + w->p.fr.saveprevrange_x;
		//http://stackoverflow.com/questions/41796832/smooth-zoom-with-mouse-in-mandelbrot-set-c?rq=1
		//http://stackoverflow.com/questions/14097559/zooming-in-on-mandelbrot-set-fractal-in-java
		w->p.fr.c_r = (w->p.fr.x / w->p.fr.zoomf) + w->p.fr.x1;
		w->p.fr.c_i = (w->p.fr.y / w->p.fr.zoomf) + w->p.fr.y1;
		w->p.fr.z_r = 0;
		w->p.fr.z_i = 0;
		/*printf("c_r: %f\n", w->p.fr.c_r);
		printf("c_i: %f\n", w->p.fr.c_i);*/
	}
}

int			fractal(t_wind *w)
{
	float tmp;
	float i;
	double intigralX;
	double intigralY;

	// Set range and mouse position 
	// in range coordonnates (x1-x2, y1-y2)
	w->p.fr.mouse_xf = ((float)w->p.fr.mouse_x/100);
	w->p.fr.mouse_yf = ((float)w->p.fr.mouse_y/100);
	w->p.fr.range_x = w->p.fr.x2 - w->p.fr.x1;
	w->p.fr.range_y = w->p.fr.y2 - w->p.fr.y1;
	w->p.fr.centerp_x = w->p.fr.x1 + (w->p.fr.range_x / 2);
	w->p.fr.centerp_y = w->p.fr.y1 + (w->p.fr.range_y / 2);
	//calc_imgsize(w);
	//before_zoom(w);
	printf("x1: %f\n", w->p.fr.x1);
	printf("x2: %f\n", w->p.fr.x2);
	printf("y1: %f\n", w->p.fr.y1);
	printf("y2: %f\n", w->p.fr.y2);
	intigralX = (w->p.fr.range_x / w->width);
	intigralY = (w->p.fr.range_y / w->height);
	printf("intigralY: %f\n", intigralY);
	printf("intigralX: %f\n", intigralX);

	w->p.fr.x = w->p.fr.x1; // set start to x min;
	/*w->p.fr.stepx = 1;
	w->p.fr.stepy = 1;*/
	while (w->p.fr.x < w->width)
	{
		w->p.fr.y = w->p.fr.y1; // set start to y min;
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
				draw_pointf(w, w->p.fr.x, w->p.fr.y, 0);
			else
				draw_pointf(w, w->p.fr.x, w->p.fr.y, i);
			w->p.fr.y += (intigralY * 100);
			//w->p.fr.y += w->p.fr.stepy;
		}
		w->p.fr.x += (intigralX * 100);
		//w->p.fr.x += w->p.fr.stepx;
	}
	/*printf("pos x souris: %d\n", w->p.fr.mouse_x);
	printf("pos y souris: %d\n", w->p.fr.mouse_y);
	printf("Julia Cx(Ci): %f\n", (float)((float)w->p.fr.mouse_y/(float)w->p.fr.img_y) * 0.3); // Max value 0.3
	printf("Julia Cy(Cr): %f\n", (float)((float)w->p.fr.mouse_x/(float)w->p.fr.img_x) * 0.02); // Max value 0.2*/
	return (0);
}
