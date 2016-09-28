

NAME=fract_ol
SRC=	main.c \
		fractal.c \
		fract_ol.c \
		create_new_window.c \
		create_new_img.c \
		matrice_rotation.c \
		draw_line.c \
		key_function.c
OBJ=${SRC:.c=.o}
LIB= -L libft -lft
LIB2= -L minilibx -lmlx
LIB3= -L /usr/include/X11/ -lXext -lX11
FLAG= -Wall -Werror -Wextra #Linux
#FLAG=-Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit #MAC

all: $(NAME)

$(NAME):	$(SRC)
	make -C libft
	make -C minilibx
	gcc $(FLAG) -o $(NAME) $(SRC) -lm  $(LIB) $(LIB2) $(LIB3)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
