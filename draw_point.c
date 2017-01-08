#include "fract_ol.h"

t_rgbcolor			get_inbetweencolor(t_rgbcolor start, t_rgbcolor end, t_wind *w, int z)
{
	int			percent;
	int			min;
	int			max;
	t_rgbcolor	col;
	/*
	ft_putstr("start.r:");
	ft_putnbr(start.r);
	ft_putstr("g:");
	ft_putnbr(start.g);
	ft_putstr("b:");
	ft_putnbr(start.b);
	ft_putstr("end.r:");
	ft_putnbr(end.r);
	ft_putstr("g:");
	ft_putnbr(end.g);
	ft_putstr("b:");
	ft_putnbr(end.b);
	ft_putchar('\n');
*/
	min = w->p.color.min;
	max = w->p.color.max;
	percent = 100 - ((max-min) - (z - min))*100/(max-min);// Calcul du pourcentage
	//get_percent(w->p.color.min, w->p.color.max, z);
	/*ft_putstr("pourcentage");
	ft_putnbr(perc);
	ft_putchar('\n');*/
	col.r = ((end.r - start.r)*percent/100) + start.r;// Calcul de la couleur
	col.g = ((end.g - start.g)*percent/100) + start.g;
	col.b = ((end.b - start.b)*percent/100) + start.b;
	/*ft_putstr("col.r:");
	ft_putnbr(col.r);
	ft_putstr("g:");
	ft_putnbr(col.g);
	ft_putstr("b:");
	ft_putnbr(col.b);
	ft_putchar('\n');*/
	return (col);
}
/*
t_rgbcolor			get_color(t_wind *w, int z)
{
	t_rgbcolor	color;

	w->p.color.bot = hexatorgb(w->p.color.hexa_bot);
	w->p.color.mid = hexatorgb(w->p.color.hexa_mid);
	w->p.color.top = hexatorgb(w->p.color.hexa_top);
	if (z <= w->p.color.lowl)
		color = hexatorgb(w->p.color.hexa_bot);
	else if (z > w->p.color.lowl && z < w->p.color.midl)
	{
		w->p.color.min = w->p.color.lowl; //pr calcul du pourcentage max
		w->p.color.max = w->p.color.midl; //pr calcul du pourcentage max
		color = get_inbetweencolor(w->p.color.bot, w->p.color.mid, w, z);
	}
	else if (z == w->p.color.midl)
		color = hexatorgb(w->p.color.hexa_mid);
	else if (z > w->p.color.midl && z < w->p.color.topl)
	{
		w->p.color.min = w->p.color.midl; //pr calcul du pourcentage max
		w->p.color.max = w->p.color.topl; //pr calcul du pourcentage max
		color = get_inbetweencolor(w->p.color.mid, w->p.color.top, w, z);
	}
	else
		color = hexatorgb(w->p.color.hexa_top);
		//color = hexatorgb("0x9E11BF"); //Get color from standard affectation
	return (color);
}*/

void			draw_point(t_wind *w, int x, int y, char *hexacolor)
{
	t_rgbcolor	rgbcolor;

	rgbcolor = hexatorgb(hexacolor);
	*(w->img.pxl_ptr + (y * w->img.size_line) +
	(x * w->img.octet_per_pixel)) = rgbcolor.r;
	*(w->img.pxl_ptr + (y * w->img.size_line) +
	(x * w->img.octet_per_pixel) + 1) = rgbcolor.g;
	*(w->img.pxl_ptr + (y * w->img.size_line) +
	(x * w->img.octet_per_pixel) + 2) = rgbcolor.b;
}

void			draw_pointf(t_wind *w, int x, int y, int z)
{
	t_rgbcolor	rgbcolor;

	rgbcolor = hexatorgb(w->p.fr.hexa_bg);
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel)) = (z*255)/w->p.fr.it_max;
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel) + 1) = rgbcolor.g;
	*(w->img.pxl_ptr + (y * w->img.size_line) + (x * w->img.octet_per_pixel) + 2) = rgbcolor.r;
}
