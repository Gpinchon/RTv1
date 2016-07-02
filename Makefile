# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/24 18:08:48 by gpinchon          #+#    #+#              #
#    Updated: 2016/07/02 13:11:31 by gpinchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= RT
SRC	=	./srcs/main.c					\
		./srcs/light_computation.c		\
		./srcs/intersections.c			\
		./srcs/intersect_cone.c			\
		./srcs/intersect_calc.c			\
		./srcs/primitives_creation.c	\
		./srcs/normal_computation.c		\
		./srcs/camera.c					\
		./srcs/keys.c					\
		./srcs/z_buffer.c				\
		./srcs/scene.c					\
		./srcs/iterate_through_pixel.c	\
		./srcs/raytrace.c				\
		./srcs/mtlightcreate.c

OBJ	= $(SRC:.c=.o)
CC	= gcc
BASE_DIR = ./includes/mlx_framework/

$(info RT Makefile says)
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
INCLUDE = -I ./includes/ -I $(BASE_DIR) -I $(BASE_DIR)libft/includes/ -I ./includes/adv_math/ -I $(MLX_PATH)
CFLAGS	= -Ofast -Wall -Wextra -Werror $(INCLUDE)

define colorecho
      @tput setaf 6
      @echo $1
      @tput sgr0
endef

NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
ERROR_COLOR=\033[31;01m
WARN_COLOR=\033[33;01m
 
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

$(NAME): $(OBJ)
	$(call colorecho, Compiling mlx_framework lib...)
	@make -s -C $(BASE_DIR)
	$(call colorecho, Compiling adv_math lib...)
	@make -s -C ./includes/adv_math/
	$(call colorecho, Compiling RT binary...)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)


%.o: %.c
	@echo -n Compiling $@...
	@($(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<)
	@echo "$(OK_STRING)"

all: $(NAME)

clean:
	$(call colorecho, Cleaning RT)
	rm -f $(OBJ)
	$(call colorecho, Cleaning mlx_framework lib...)
	@make -C $(BASE_DIR) clean
	$(call colorecho, Cleaning adv_math lib...)
	@make -C ./includes/adv_math/ clean

fclean:
	$(call colorecho, Fully cleaning RT)
	rm -f $(OBJ) $(NAME)
	$(call colorecho, Fully cleaning mlx_framework lib...)
	@make -C $(BASE_DIR) fclean
	$(call colorecho, Fully cleaning adv_math lib...)
	@make -C ./includes/adv_math/ fclean

re: fclean
	make

.PHONY: all clean fclean re $(NAME)
