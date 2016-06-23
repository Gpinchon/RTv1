NAME	= libmlx_framework.a
SRC		=	images.c		\
			images2.c		\
			windows.c		\
			new_window.c	\
			objects.c		\
			framework.c 	\
			callback.c		\
			rgba.c			\
			rgb.c			\
			errors.c		\
			keys.c

OBJ		= $(SRC:.c=.o)
CC		= gcc

ifeq ($(shell uname), Darwin)
$(info Mac OS detected !)
MLX_PATH = ./minilibx_mac/
LIBS	= -L ./ -L ./libft/ -lm -lft -lmlx -framework OpenGL -framework Appkit
else
$(info $(shell uname) detected !)
MLX_PATH = ./minilibx_xorg/
LIBS	= -L ./ -L $(MLX_PATH) -L ./libft/ -lm -lft -lmlx -lXext -lX11
endif
CFLAGS	= -Ofast -Wall -Wextra -Werror -I ./ -I $(MLX_PATH) -I ./libft/

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)
	cd ./libft/ && $(MAKE)
	cd $(MLX_PATH) && $(MAKE)

all: $(NAME)
	cd ./libft/ && $(MAKE) all
	cd $(MLX_PATH) && $(MAKE) all

clean:
	cd ./libft/ && $(MAKE) clean
	cd $(MLX_PATH) && $(MAKE) clean
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
	cd ./libft/ && $(MAKE) re
	cd $(MLX_PATH) && $(MAKE) re
