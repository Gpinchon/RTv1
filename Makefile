NAME	= RT
SRC	=	./main.c				\
		./light_computation.c	\
		./intersections.c

OBJ	= $(SRC:.c=.o)
CC	= gcc
BASE_DIR = ./includes/mlx_framework/

ifeq ($(shell uname), Darwin)
$(info Mac OS detected !)
MLX_PATH = $(BASE_DIR)minilibx_mac/
MLX_LIBS = -lmlx -framework OpenGL -framework Appkit
else
$(info $(shell uname) detected !)
MLX_PATH = $(BASE_DIR)minilibx_xorg/
MLX_LIBS = -lmlx -lXext -lX11
endif

LIBS	= -L ./includes/ -L $(BASE_DIR) -L $(BASE_DIR)libft/ -L ./includes/adv_math/ -L $(MLX_PATH) -lm -ladv_math -lmlx_framework -lft $(MLX_LIBS)
CFLAGS	= -Ofast -Wall -Wextra -Werror -I ./includes/ -I $(BASE_DIR) -I $(BASE_DIR)libft/ -I ./includes/adv_math/ -I $(MLX_PATH)

all: $(NAME)

$(NAME):$(OBJ)
	cd $(BASE_DIR) && $(MAKE)
	cd ./includes/adv_math/ && $(MAKE)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LIBS)

clean:
	cd $(BASE_DIR) && $(MAKE) clean
	cd ./includes/adv_math/ && $(MAKE) clean
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:
	cd $(BASE_DIR) && $(MAKE) re
	cd ./includes/adv_math/ && $(MAKE) re
	fclean $(NAME)

.PHONY: all clean fclean re
