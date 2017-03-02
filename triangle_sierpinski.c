
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
#define TX 758
#define TY 655

void				draw_trianglef(t_wind *w, t_triangle t, char *hexcolor)
{
	draw_2dline(w, t.dl, t.dr, hexcolor); // On dessine les tours du triangle:
	draw_2dline(w, t.dr, t.dt, hexcolor);
	draw_2dline(w, t.dt, t.dl, hexcolor);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr_img, w->img.x, w->img.y);
}

/* fonction récursive, qui a pour paramètres :
 *    les coordonnées (x, y) de l'extrémité gauche de la base d'un triangle équilatéral, 
 *       a la longueur d'un de ses cotés et 
 *          n le nombre d'itérations */

static void			triangle_sierpinski(t_wind *w, double x, double y, double a, int n)
{
	double		b;
	t_triangle	t;
	t_triangle	t2;

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
		draw_trianglef(w, t, "0xFFFFFF");
		/* et on supprime le petit triangle central */
		t2.dl.x = x + (a / 2);
		t2.dl.y = y;
		t2.dr.x = x + 3 * a / 4;
		t2.dr.y = y + b / 2;
		t2.dt.x = x + (a / 4);
		t2.dt.y = (y + b / 2);
		draw_trianglef(w, t2, "0xFFFFFF");
		/* appels récursifs */
		triangle_sierpinski(w, x, y, a/2, n-1);
		triangle_sierpinski(w, x+a/2, y, a/2, n-1);
		triangle_sierpinski(w, x+a/4, y+b/2, a/2, n-1);
	}
}

int triangle_sierpinski_main(t_wind *w)
{
	unsigned long n;
	//n = 5; // level of detail
	ft_putstr("w->p.fr.zoom:");
	ft_putnbr(w->p.fr.zoom);
	ft_putstr("\n");
	ft_putstr("w->p.fr.it_max:");
	ft_putnbr(w->p.fr.it_max);
	ft_putstr("\n");
	ft_putstr("w->img.width:");
	ft_putnbr(w->img.width);
	ft_putstr("\n");
	ft_putstr("w->img.height:");
	ft_putnbr(w->img.height);
	ft_putstr("\n");
	n = w->p.fr.it_max;
	//ft_putendl("before triangle_sierpinski");
	triangle_sierpinski(w, OX, OY + w->img.height, w->img.width, (int)n);
	//ft_putendl("after triangle_sierpinski");
	return 0;
}
