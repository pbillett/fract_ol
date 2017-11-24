UNAME := $(shell uname)
NAME=fractol
SRC=	src/main.c \
		src/fractol.c \
		src/fractal.c \
		src/set_julia.c \
		src/burningship.c \
		src/triangle_sierpinski.c \
		src/draw_line.c \
		src/set_parameters_tline.c \
		src/create_new_window.c \
		src/create_new_img.c \
		src/draw_point.c \
		src/rgbtohexa.c \
		src/key_function.c \
		src/ft_randcolorrgb.c \
		src/mouse_function.c \
		src/put_info.c \
		src/error.c
OBJ=${SRC:.c=.o}

ifeq ($(UNAME), Darwin) # MAC
MINILIBX= make -C minilibx_macos
LIB= -lm -L libft -lft
LIB2= -L minilibx_macos -L/usr/local/lib/ -I/usr/local/include
LIB3= -lmlx -framework OpenGL -framework AppKit
FLAG= -Wall -Werror -Wextra
CLEAN= make clean -C minilibx_macos/
KEY= 1
endif
ifeq ($(UNAME), Linux) # LINUX :
MINILIBX= make -C minilibx
LIB= -lm -L libft -lft
LIB2= -L minilibx -lmlx
LIB3= -L /usr/include/X11/ -lXext -lX11
FLAG= -Wall -Werror -Wextra
CLEAN= make clean -C minilibx/
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
	$(CLEAN)

re: fclean all

.PHONY: all clean fclean re
