

UNAME := $(shell uname)
NAME=fractol
SRC=	main.c \
		fractol.c \
		fractal.c \
		set_julia.c \
		triangle_sierpinski.c \
		draw_line.c \
		set_parameters_tline.c \
		create_new_window.c \
		create_new_img.c \
		draw_point.c \
		rgbtohexa.c \
		key_function.c \
		ft_randcolorrgb.c \
		mouse_function.c \
		put_info.c \
		error.c
OBJ=${SRC:.c=.o}

ifeq ($(UNAME), Darwin) # MAC
MINILIBX= make -C libft/inc/minilibx_macos
LIB= -lm -L libft -lft
LIB2= -L libft/inc/minilibx_macos -L/usr/local/lib/ -I/usr/local/include
LIB3= -lmlx -framework OpenGL -framework AppKit
FLAG= -Wall -Werror -Wextra
CLEAN= make clean -C libft/inc/minilibx_macos/
KEY= 1
endif
ifeq ($(UNAME), Linux) # LINUX :
MINILIBX= make -C libft/inc/minilibx
LIB= -lm -L libft -lft
LIB2= -L libft/inc/minilibx -lmlx
LIB3= -L /usr/include/X11/ -lXext -lX11
FLAG= -Wall -Werror -Wextra
CLEAN= make clean -C libft/inc/minilibx/
KEY= 2
endif

all: $(NAME)

$(NAME):	$(SRC)
	make -C libft
	$(MINILIBX)
	gcc $(FLAG) -o $(NAME) $(SRC) $(LIB) $(LIB2) $(LIB3) -D MACROKEY=$(KEY)

clean:
	rm -rf $(OBJ)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft
	#$(CLEAN)

re: fclean all

.PHONY: all clean fclean re
