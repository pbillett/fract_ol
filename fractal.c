#include "fract_ol.h"

void		calc_imgsize(t_wind *w)
{
	//w->p.fr.img_x = (w->p.fr.x2 - w->p.fr.x1) * w->p.fr.zoom;
	//w->p.fr.img_y = (w->p.fr.y2 - w->p.fr.y1) * w->p.fr.zoom;
	//Methode taille image fixe:
	w->p.fr.img_x = 270;
	w->p.fr.img_y = 240;
	w->p.fr.zoom_x = w->p.fr.img_x/(w->p.fr.x2 - w->p.fr.x1);
	w->p.fr.zoom_y = w->p.fr.img_y/(w->p.fr.y2 - w->p.fr.y1);
	printf("img_x: %d\n", w->p.fr.img_x);
	printf("img_y: %d\n", w->p.fr.img_y);
}

static void		set_nbrcomplexandz(t_wind *w)
{
	if (ft_strcmp(w->p.fr.name, "julia") == 0)
	{
		w->p.fr.c_r = 0.285;
		w->p.fr.c_i = 0.01;
		//w->p.fr.z_r = w->p.fr.x/w->p.fr.zoom + w->p.fr.x1;
		//w->p.fr.z_i = w->p.fr.y/w->p.fr.zoom + w->p.fr.y1;
		//Methode taille image fixe:
		w->p.fr.z_r = w->p.fr.x/w->p.fr.zoom_x + w->p.fr.x1;
		w->p.fr.z_i = w->p.fr.y/w->p.fr.zoom_y + w->p.fr.y1;
		//Methode taille image fixe:
	}
	else
	{
		//w->p.fr.c_r = w->p.fr.x/w->p.fr.zoom + w->p.fr.x1;
		//w->p.fr.c_i = w->p.fr.y/w->p.fr.zoom + w->p.fr.y1;
		//Methode taille image fixe:
		w->p.fr.c_r = w->p.fr.x/w->p.fr.zoom_x + w->p.fr.x1;
		w->p.fr.c_i = w->p.fr.y/w->p.fr.zoom_y + w->p.fr.y1;
		w->p.fr.z_r = 0;
		w->p.fr.z_i = 0;
	}
}

int			fractal(t_wind *w)
{
	float tmp;
	float i;
	
	//if (w->p.fr.zoom_x != 100)
	//{
		w->p.fr.mouse_xf =  w->p.fr.x1 + ((float)w->p.fr.mouse_x/100);
		w->p.fr.mouse_yf = w->p.fr.y1 + ((float)w->p.fr.mouse_y/100);
		printf("mouse_xf: %f\n", w->p.fr.mouse_xf);
		printf("mouse_yf: %f\n", w->p.fr.mouse_yf);
		printf("zoom_x: %d\n", w->p.fr.zoom_x);
		printf("zoom_y: %d\n", w->p.fr.zoom_y);
		printf("h: %f\n", w->p.fr.h);
		w->p.fr.range_x = w->p.fr.x2 - w->p.fr.x1;
		w->p.fr.range_y = w->p.fr.y2 - w->p.fr.y1;
		printf("range_x: %f\n", w->p.fr.range_x);
		printf("range_y: %f\n", w->p.fr.range_y);
		/*
		w->p.fr.x1 = w->p.fr.mouse_xf - w->p.fr.range_x;
		w->p.fr.x2 = w->p.fr.range_x - w->p.fr.mouse_xf;
		w->p.fr.y1 = w->p.fr.mouse_yf - w->p.fr.range_y;
		w->p.fr.y2 = w->p.fr.range_y - w->p.fr.mouse_yf;
		*/
		
		w->p.fr.x1 = -(w->p.fr.mouse_xf - w->p.fr.h) - (w->p.fr.range_x/2);
		//w->p.fr.x2 = (w->p.fr.mouse_xf - w->p.fr.h) - (w->p.fr.range_x/2);
		w->p.fr.x2 = w->p.fr.x1 + w->p.fr.range_x;
		w->p.fr.y1 = -(w->p.fr.mouse_yf - w->p.fr.h) - (w->p.fr.range_y/2);
		w->p.fr.y2 = w->p.fr.y1 + w->p.fr.range_y;
		//w->p.fr.x1 = (w->p.fr.mouse_xf - w->p.fr.h);
		//w->p.fr.x2 = (w->p.fr.mouse_xf + w->p.fr.h);
		//w->p.fr.y1 = (w->p.fr.mouse_yf - w->p.fr.h);
		//w->p.fr.y2 = (w->p.fr.mouse_yf + w->p.fr.h);
		printf("x1: %f\n", w->p.fr.x1);
		printf("x2: %f\n", w->p.fr.x2);
		printf("y1: %f\n", w->p.fr.y1);
		printf("y2: %f\n", w->p.fr.y2);
	//}
	//calc_imgsize(w);
	w->p.fr.x = 0;
	while (w->p.fr.x < w->p.fr.img_x)
	{
		w->p.fr.y = 0;
		while (w->p.fr.y < w->p.fr.img_y)
		{
			set_nbrcomplexandz(w);
			i = 0;
			while ((w->p.fr.z_r*w->p.fr.z_r + w->p.fr.z_i*w->p.fr.z_i) < 4 && i < w->p.fr.it_max)
			{
				tmp = w->p.fr.z_r;
				w->p.fr.z_r = (w->p.fr.z_r*w->p.fr.z_r - w->p.fr.z_i*w->p.fr.z_i) + w->p.fr.c_r;
				w->p.fr.z_i = 2*tmp*w->p.fr.z_i + w->p.fr.c_i;
				i++;
			}
			if (i == w->p.fr.it_max)
				draw_point(w, w->p.fr.x, w->p.fr.y, 0);
			else
				draw_point(w, w->p.fr.x, w->p.fr.y, i);
			w->p.fr.y++;
		}
		w->p.fr.x++;
	}
	return (0);
}
