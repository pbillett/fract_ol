#include "fractol.h"

// http://sdz.tdct.org/sdz/dessiner-la-fractale-de-mandelbrot.html
// https://www.codeproject.com/Articles/7513/Mandelbrot-Set-for-C
/*
void		calc_imgsize(t_wind *w)
{
	w->p.fr.img_x = (w->p.fr.x2 - w->p.fr.x1) * (w->p.fr.zoomf);
	w->p.fr.img_y = (w->p.fr.y2 - w->p.fr.y1) * (w->p.fr.zoomf);
	printf("img_x calc: %d\n", w->p.fr.img_x);
	printf("img_y calc: %d\n", w->p.fr.img_y);
}
*/
double interpolate(double start, double end, double interpolation)
{
    return start + ((end - start) * interpolation);
}

void apply_zoom(t_mandelbrot *fr, double mouseRe, double mouseIm, double zoomFactor)
{
	double interpolation = 1.0 / zoomFactor;
	fr->x1 = interpolate(mouseRe, fr->x1, interpolation);
	fr->y1 = interpolate(mouseIm, fr->y1, interpolation);
	fr->x2 = interpolate(mouseRe, fr->x2, interpolation);
	fr->y2 = interpolate(mouseIm, fr->y2, interpolation);
}

static void		set_nbrcomplexandz(t_wind *w, int x, int y)
{
	int			mousecenter_x;
	int			mousecenter_y;

	mousecenter_x = w->width/2 - w->p.fr.mouse_x;
	mousecenter_y = w->height/2 - w->p.fr.mouse_y;
	if (ft_strcmp(w->p.fr.name, "julia") == 0)
	{
		//w->p.fr.c_r = 0.285;
		//w->p.fr.c_i = 0.01;
		// REF EXPLICATION CONSTANTE DE JULIA:
		// http://maths.wikidot.com/mandelbrot-et-julia
		// On fait varier la constante C de julia, en fonction de la position
		// x, et y de notre souris sur l'écran :
		// Je rset ma position de la souris avec un point 0,0,0 au centre de l'ecran
		w->p.fr.fra->c_r = ((float)mousecenter_y/(float)w->p.fr.img_y) * 2; //Cx =  0.3 valeur max
		w->p.fr.fra->c_i = ((float)mousecenter_x/(float)w->p.fr.img_x) * 2; // Cy = 0.02 valeur max
		w->p.fr.fra->z_r = x / w->p.fr.zoom + w->p.fr.fra->x1;
		w->p.fr.fra->z_i = y / w->p.fr.zoom + w->p.fr.fra->y1;
	}
	else if (ft_strcmp(w->p.fr.name, "mandelbrot") == 0)
	{
		// https://deptinfo-ensip.univ-poitiers.fr/FILES/TPS/FRACTALES/zoom.php
		//https://github.com/Remaii/Fractol
		//http://stackoverflow.com/questions/41796832/smooth-zoom-with-mouse-in-mandelbrot-set-c?rq=1
		//http://stackoverflow.com/questions/14097559/zooming-in-on-mandelbrot-set-fractal-in-java
		//w->p.fr.fra->c_r = (x / w->p.fr.zoomf) + w->p.fr.fra->x1 + ((w->p.fr.fra->x2 - w->p.fr.fra->x1) / w->width) + w->p.fr.key_x;
		//w->p.fr.fra->c_i = (y / w->p.fr.zoomf) + w->p.fr.fra->y1 + ((w->p.fr.fra->y2 - w->p.fr.fra->y1) / w->height) + w->p.fr.key_y;
		/*printf("before c_a c_r\n");
		printf("w->p.fr.fra->x1 : %.2f\n", w->p.fr.fra->x1);*/
		//printf("(x / w->p.fr.zoom_x) : %.2f\n", (x / w->p.fr.zoom_x));
		/*printf("(x / w->p.fr.zoom_x) : %.2f\n", (x / w->p.fr.zoom_x) + w->p.fr.fra->x1);*/
		w->p.fr.fra->c_r = x / w->p.fr.zoom_x + w->p.fr.fra->x1;
		//printf("first ok\n");
		//printf("(x / w->p.fr.zoom_y) : %.2f\n", w->p.fr.fra->y1);
		//printf("(x / w->p.fr.zoom_y) : %.2f\n", (float)y);
		//printf("(x / w->p.fr.zoom_y) : %.2f\n", (y / w->p.fr.zoom_y) + w->p.fr.fra->y1);
		w->p.fr.fra->c_i = y / w->p.fr.zoom_y + w->p.fr.fra->y1;
		//printf("first ok\n");
		//printf("after c_a c_r\n");
		/*w->p.fr.fra->c_r = ((w->p.fr.fra->x2 - w->p.fr.fra->x1) / w->width) + w->p.fr.fra->x1;
		w->p.fr.fra->c_i = ((w->p.fr.fra->y2 - w->p.fr.fra->y1) / w->height) + w->p.fr.fra->y1;*/
		w->p.fr.fra->z_r = 0 + w->p.fr.mouse_x;
		w->p.fr.fra->z_i = 0 + w->p.fr.mouse_y;
		//printf("after z_r z_i\n");
	}
}

void mydraw(t_wind *w, int x, int y, t_rgbcolor color, int i)
{
	int index;

	index = x * (w->img.bits_per_pixel / 8) + (y * w->img.size_line);
		if (i == w->p.fr.it_max)
		{
			w->img.pxl_ptr[index] = 0;
			w->img.pxl_ptr[index + 1] = 0;
			w->img.pxl_ptr[index + 2] = 0;
		}
		else
		{
//			w->img.pxl_ptr[index] = i * color.b;
			w->img.pxl_ptr[index] = i * color.b;
			w->img.pxl_ptr[index + 1] = i * color.g;
			w->img.pxl_ptr[index + 2] = i * color.r;
		}
}

int					fractal(t_wind *w)
{
	int				i;
	//int				x;
	//int				y;
//	t_gradientcol	gradecolor;
	t_rgbcolor		color;

	color.r = 257;
	color.g = 20;
	color.b = 210;
	printf("x1: %f\n", w->p.fr.fra->x1);
	printf("x2: %f\n", w->p.fr.fra->x2);
	printf("y1: %f\n", w->p.fr.fra->y1);
	printf("y2: %f\n", w->p.fr.fra->y2);
	//w->p.fr.c_r = w->p.fr.x1 + w->p.fr.key_x; // set start to x min;
	//printf("it_max:%d\n", w->p.fr.it_max);
	w->p.fr.x = 0;
	while (w->p.fr.x < w->img.width)
	{
		//w->p.fr.c_i = w->p.fr.y1 + w->p.fr.key_y; // set start to y min;
		w->p.fr.y = 0;
		while (w->p.fr.y < w->img.height)
		{
			set_nbrcomplexandz(w, w->p.fr.x, w->p.fr.y);
			i = 0;
			while ((ft_squared(w->p.fr.fra->z_r) + ft_squared(w->p.fr.fra->z_i)) < 4 && i < w->p.fr.it_max)
			{
				w->p.fr.fra->tmp = w->p.fr.fra->z_r;
				w->p.fr.fra->z_r = (ft_squared(w->p.fr.fra->z_r) - ft_squared(w->p.fr.fra->z_i)) + w->p.fr.fra->c_r;
				w->p.fr.fra->z_i = 2*w->p.fr.fra->tmp*w->p.fr.fra->z_i + w->p.fr.fra->c_i;
//				printf("i: %d\n", i);
				/*printf("w->p.fr.it_max: %d\n", w->p.fr.it_max);
				printf("w->p.fr.it_max: %.2f\n", (w->p.fr.fra->z_r));
				printf("w->p.fr.fra->z_r: %.2f\n", (ft_squared(w->p.fr.fra->z_r)));
				printf("w->p.fr.fra->z_i: %.2f\n", (ft_squared(w->p.fr.fra->z_i)));
				printf("w->p.fr.fra->c_r: %.2f\n", (ft_squared(w->p.fr.fra->c_r)));
				printf("w->p.fr.it_max: %.2f\n", (ft_squared(w->p.fr.fra->z_r) + ft_squared(w->p.fr.fra->z_i)));*/
				//ft_putnbr(i);
				i++;
				mydraw(w, w->p.fr.x, w->p.fr.y, color, i);
//				if (i == w->p.fr.it_max)
//					draw_pointf(w, w->p.fr.x, w->p.fr.y, 0x000000);
//				else
//				{
//					if (w->p.fr.colorset == 0) //first color mode (change with spacebar)
//						draw_pointf(w, w->p.fr.x, w->p.fr.y, mlx_get_color_value(w->mlx, i*255 / w->p.fr.it_max));
//					else
//					{
//						gradecolor = ultra_fractalgrade();
//						color = colorgrade(i/100, gradecolor);
//						draw_point(w, w->p.fr.x, w->p.fr.y, rgbtohexa(color));
//					}
//				}
			}
//			printf("fin square\n");
			w->p.fr.y++;
		}
		w->p.fr.x++;
	}
	put_info(w);
	printf("the end\n");
	return (0);
}
