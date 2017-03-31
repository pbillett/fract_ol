
/* pour compiler taper en ligne de commande :
 *    gcc triangle.c -o triangle `allegro-config --libs`
 *       pour exécuter taper triangle suivi du nombre d'itérations :
 *          triangle 7
 *             */

// Ref explication du triangle de sierpinski ici
// https://fr.wikipedia.org/wiki/Triangle_de_Sierpi%C5%84ski

#include "fractol.h"
#include <stdlib.h>
#include <math.h>

#define OX 5
#define OY 5

void				draw_trianglef(t_wind *w, t_triangle t, t_rgbcolor color)
{
	//ft_putendl("before draw_2dline");

	//ft_randcolorrgb(w);
	draw_2dline(w, t.dl, t.dr, color); // On dessine les tours du triangle:
	/*ft_putendl("before1 draw_2dline");
	ft_putstr(" t.dr x:");
	ft_putnbr(t.dr.x);
	ft_putstr(" t.dr y:");
	ft_putnbr(t.dr.y);
	ft_putstr(" t.dr z:");
	ft_putnbr(t.dr.z);
	ft_putstr(" t.dr x:");
	ft_putnbr(t.dt.x);
	ft_putstr(" t.dr y:");
	ft_putnbr(t.dt.y);
	ft_putstr(" t.dr z:");
	ft_putnbr(t.dt.z);
	ft_putstr("\n");*/
	//ft_randcolorrgb(w);
	draw_2dline(w, t.dr, t.dt, color);
	//ft_putendl("before2 draw_2dline");
	//ft_randcolorrgb(w);
	draw_2dline(w, t.dt, t.dl, color);
	//ft_putendl("before3 draw_2dline");
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
	//ft_putendl("after draw_2dline");
}

/* fonction récursive, qui a pour paramètres :
 *    les coordonnées (x, y) de l'extrémité gauche de la base d'un triangle équilatéral, 
 *       a la longueur d'un de ses cotés et 
 *          n le nombre d'itérations */

static void			triangle_sierpinski(t_wind *w, double x, double y, double a, int n)
{
	double			b;
	t_triangle		t;
	t_triangle		t2;

	b = -a*sqrt(3.0)/2;
	/* négatif à cause de l'orientation 
	 *      de l'axe des ordonnées vers le bas */
	if (n>0)
	{
		/*ft_putstr("n:");
		ft_putnbr(n);
		ft_putstr("\n");*/
		/* on dessine un triangle plein */
		t.dl.x = x;
		t.dl.y = y;
		t.dl.z = 0;
		t.dr.x = x + a;
		t.dr.y = y;
		t.dr.z = 0;
		t.dt.x = x + (a / 2);
		t.dt.y = (y + b);
		t.dt.z = 0;
		draw_trianglef(w, t, FG(color));
		/* et on supprime le petit triangle central */
		t2.dl.x = x + (a / 2);
		t2.dl.y = y;
		t2.dr.x = x + 3 * a / 4;
		t2.dr.y = y + b / 2;
		t2.dt.x = x + (a / 4);
		t2.dt.y = (y + b / 2);
		draw_trianglef(w, t2, FG(color));
		/* appels récursifs */
		triangle_sierpinski(w, x, y, a/2, n-1);
		triangle_sierpinski(w, x+a/2, y, a/2, n-1);
		triangle_sierpinski(w, x+a/4, y+b/2, a/2, n-1);
	}
}

int					triangle_sierpinski_main(t_wind *w)
{
	unsigned long	n;
	//n = 5; // level of detail
	//printf("w->p.fr.coeff: %.3f\n", w->p.fr.coeff);
	//printf("w->p.fr.triwidth: %.3f\n", d->triwidth);
	ft_putstr("w->p.fr.zoom:");
	ft_putnbr(w->p.fr.zoom);
	ft_putstr("\n");
	ft_putstr("w->p.fr.it_max:");
	ft_putnbr(w->p.fr.it_max);
	ft_putstr("\n");
	printf("pos_x de start:%.3f\n", ((double)(w->width/2) - (double)(w->p.fr.triwidth/2)) / FG(zoom_x));
	printf("FG(zoom_x):%.3f\n", FG(zoom_x));
	/*
	ft_putstr("w->width:");
	ft_putnbr(w->width);
	ft_putstr("\n");
	ft_putstr("w->height:");
	ft_putnbr(w->height);
	ft_putstr("\n");*/
	if (w->p.fr.it_max >= 4)
		n = w->p.fr.it_max / 4;
	else
		n = 1;
	//if(!w->p.fr.ptriwidth)
		//w->p.fr.ptriwidth = 0;
	/*else
		ptriwidth = w->width/10;*/
	//ft_putendl("before triangle_sierpinski");
	//triangle_sierpinski(w, ((double)(w->width/2) - (double)(w->p.fr.triwidth/2)), OY + w->p.fr.triheight, w->p.fr.triwidth, (int)n);
	triangle_sierpinski(w, 0, OY + w->p.fr.triheight, w->p.fr.triwidth, (int)n);
	//ft_putendl("after triangle_sierpinski");
	return 0;
}
