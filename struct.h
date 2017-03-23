
# ifndef STRUCT_H
# define STRUCT_H

typedef struct			s_fractal
{
	char				*name;
	struct s_mandelbrot *fra;
	struct s_mandelbrot *mdb;
	struct s_mandelbrot *jul;
	float				x;
	float				y;
	int					img_x;
	int					img_y;
	int					colorset;
	float				range_x;
	float				range_y;
	int					zoominit;
	int					zoom;
	float				coeff;
	float				zoomspeed;
	float				quality_of_details;
	float				key_x; //To move in fractal with keyboard
	float				key_y;
	float				step;
	float				stepx;
	float				stepy;
	double				zoom_x;
	double				zoom_y;
	float				centerp_x;
	float				centerp_y;
	int					it_max;
	char				*hexa_bg;//Color
	float				h; //zoom inv
	int					mouse_x;
	int					mouse_y;
	float				mouse_xf;
	float				mouse_yf;
}						t_fractal;

typedef struct		s_mandelbrot
{
	float			x1;
	float			x2;
	float			y1;
	float			y2;
	float			c_r; //Nbr complexe
	float			c_i; //Nbr complexe
	float			z_r; //Nbr z
	float			z_i; //Nbr z
	float			tmp; //Nbr z
}					t_mandelbrot;

typedef struct		s_rgbcolor
{
	int				r;
	int				g;
	int				b;
}					t_rgbcolor;

typedef struct		s_gradientcol
{
	int				nbofcolor;
	float			*lstpos;
	t_rgbcolor		*lstcol;
}					t_gradientcol;

typedef struct		s_colorpalette
{
	char			*hexa_bot; //Color bottom in hexa
	char			*hexa_mid;
	char			*hexa_top;
	char			*hexa_axle;
	t_rgbcolor		bot; // Color in rgb
	t_rgbcolor		mid;
	t_rgbcolor		top;
	int				lowl; //Level of affection for color
	int				midl;
	int				topl;
	int				z;//dot height of field
	int				zd;//dot height of field dst
	int				min;//Min Level for percent of color
	int				max;//Max level
}					t_colorpalette;

typedef struct		s_line
{
	float			x;
	float			y;
	float			z;//For height per color
	int				xdest;
	int				ydest;
	int				zdest;
	int				sign_x;
	int				sign_y;
	int				sign_z;
	float			bigdiff;
	float			diff_x;
	float			diff_y;
	float			diff_z;
	int				midx;
	int				midy;
}					t_line;

typedef struct		s_dpoint
{
	double			x;
	double			y;
	double			z;
}					t_dpoint;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	size_t			color;
}					t_point;

typedef struct		s_triangle
{
	t_point			dl;
	t_point			dr;
	t_point			dt;
}					t_triangle;

typedef struct		s_fillsquare
{
	t_point			p;
	t_point			pr;
	t_point			pd;
	t_point			pdi;
}					t_fillsquare;

typedef struct		s_browsefile
{
	int				**tab_int;
	int				nbr_of_line; //nbr of line
	int				nbr_elem_line; //nbr elem on line
}					t_browsefile;

typedef struct		s_img
{
	void			*ptr_img;
	int				x; //position of img
	int				y;
	int				start_x; //depart print ds img
	int				start_y;
	int				width;
	int				height;
	int				padh;
	int				padv;
	int				x_centerpoint;
	int				y_centerpoint;
	int				z_centerpoint;
	char			*pxl_ptr;
	int				bits_per_pixel;
	int				size_line;
	int				octet_per_pixel;
	int				endian_type;
	t_point			point;//point
	t_point			pointd;//point destination
	t_point			r_point; //apres rotation
	t_point			r_pointd; //apres rotation
}					t_img;

typedef struct		s_params
{
	int				accentuation; //hauteur relief
	int				angle_projpara; //zoom y
	int				size_square; //zoom x
	t_point			rot; //angle de rotation
	t_dpoint		r_rot; //angle de rotation radian
	int				graphic_mode; //Mode dot/wireframe/fill
	int				view_mode; //Mode para/iso
	int				dot; //point centre carre
	int				insert;
	int				boolaxle;
	int				help;
	t_colorpalette	color;
	int				keycode;
	int				keypress;
	t_fractal		fr;
}					t_params;

typedef struct		s_rotaxle
{
	t_point			p_x;
	t_point			pd_x;
	t_point			p_y;
	t_point			pd_y;
	t_point			oldp_x;
	t_point			oldp_y;
}					t_rotaxle;

typedef struct		s_wind
{
	void			*mlx;
	void			*win;
	char			*title;
	int				width;
	int				height;
	t_point			point;
	t_img			img;
	t_browsefile	b;
	t_params		p;
	t_rotaxle		r;
}					t_wind;

#endif

