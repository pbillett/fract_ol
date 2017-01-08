#include "fract_ol.h"

void		calc_imgsize(t_wind *w)
{
	w->p.fr.img_x = (w->p.fr.x2 - w->p.fr.x1) * w->p.fr.zoom;
	w->p.fr.img_y = (w->p.fr.y2 - w->p.fr.y1) * w->p.fr.zoom;
	printf("img_x: %d\n", w->p.fr.img_x);
	printf("img_y: %d\n", w->p.fr.img_y);
}

static void		set_nbrcomplexandz(t_wind *w)
{
	if (ft_strcmp(w->p.fr.name, "julia") == 0)
	{
		w->p.fr.c_r = 0.285;
		w->p.fr.c_i = 0.01;
		w->p.fr.z_r = w->p.fr.x/w->p.fr.zoom + w->p.fr.x1;
		w->p.fr.z_i = w->p.fr.y/w->p.fr.zoom + w->p.fr.y1;
	}
	else if (ft_strcmp(w->p.fr.name, "newton") == 0)
	{
		w->p.fr.c_r = 0.285;
		w->p.fr.c_i = 0.01;
	}
	else
	{
		w->p.fr.c_r = w->p.fr.x/w->p.fr.zoom + w->p.fr.x1;
		w->p.fr.c_i = w->p.fr.y/w->p.fr.zoom + w->p.fr.y1;
		w->p.fr.z_r = 0;
		w->p.fr.z_i = 0;
		//printf("c_r: %f\n", w->p.fr.c_r);
		//printf("c_i: %f\n", w->p.fr.c_i);
	}
}

int			before_zoom(t_wind *w)
{
	printf("img_x: %d\n", w->p.fr.img_x);
	printf("img_y: %d\n", w->p.fr.img_y);

	// Set range and mouse position 
	// in range coordonnates (x1-x2, y1-y2)
	w->p.fr.mouse_xf = ((float)w->p.fr.mouse_x/100);
	w->p.fr.mouse_yf = ((float)w->p.fr.mouse_y/100);
	w->p.fr.range_x = w->p.fr.x2 - w->p.fr.x1;
	w->p.fr.range_y = w->p.fr.y2 - w->p.fr.y1;

	//On recadre en décalant tout le cadre, en haut
	//à gauche, au début du point de la souris
	w->p.fr.x1 = w->p.fr.x1 + (((float)w->p.fr.mouse_x/w->p.fr.img_x) * w->p.fr.range_x);
	w->p.fr.y1 = w->p.fr.y1 + (((float)w->p.fr.mouse_y/w->p.fr.img_y) * w->p.fr.range_y);
	//w->p.fr.x2 = w->p.fr.x1 + w->p.fr.range_x;
	//w->p.fr.y2 = w->p.fr.y1 + w->p.fr.range_y;

	printf("pos x souris: %f\n", (float)w->p.fr.mouse_x/w->p.fr.img_x);
	printf("pos y souris: %d\n", w->p.fr.mouse_y);
	return (0);
}

int			after_zoom(t_wind *w)
{
	//float	tmp_range_x;
	//float	tmp_range_y;

	//Redefinition du range:
	w->p.fr.range_x = w->p.fr.x2 - w->p.fr.x1;
	w->p.fr.range_y = w->p.fr.y2 - w->p.fr.y1;

	// Zoom relatif (par rapport au point en haut à gauche)
	// (Compensation du zoomx2 en gérant avec le range/2 pour les valeurs x2 et y2.
	// PS: (Pour voir le zoom progressif mettre range/5.)
	w->p.fr.x2 = w->p.fr.x2 - (w->p.fr.range_x/2);
	w->p.fr.y2 = w->p.fr.y2 - (w->p.fr.range_y/2);
	printf("pos img x: %d\n", w->img.x);
	printf("pos img y: %d\n", w->img.y);

	//Reutilisation du range de départ (nécessaire pour le Redécalage):
	//Redécalage en haut à gauche, au début du point
	//du précédent cadre. (soit - pos souris)
	w->p.fr.x1 = w->p.fr.x1 - (((float)w->p.fr.mouse_x/w->p.fr.img_x) * w->p.fr.range_x);
	w->p.fr.y1 = w->p.fr.y1 - (((float)w->p.fr.mouse_y/w->p.fr.img_y) * w->p.fr.range_y);
	//Puis on recale les coin x2 et y2 aussi pour éviter le décalge
	//w->p.fr.x2 = w->p.fr.x1 - w->p.fr.range_x;
	//w->p.fr.y2 = w->p.fr.y1 - w->p.fr.range_y;
	return (0);
}

int			fractal(t_wind *w)
{
	float tmp;
	float i;

	//calc_imgsize(w);
	//before_zoom(w);
	printf("x1: %f\n", w->p.fr.x1);
	printf("x2: %f\n", w->p.fr.x2);
	printf("y1: %f\n", w->p.fr.y1);
	printf("y2: %f\n", w->p.fr.y2);
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
				draw_pointf(w, w->p.fr.x, w->p.fr.y, 0);
			else
				draw_pointf(w, w->p.fr.x, w->p.fr.y, i);
			w->p.fr.y++;
		}
		w->p.fr.x++;
	}
	return (0);
}
