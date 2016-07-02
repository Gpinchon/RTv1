# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/27 21:27:07 by gpinchon          #+#    #+#              #
#    Updated: 2016/07/02 13:04:17 by gpinchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
CFLAGS	= -Ofast -Wall -Wextra -Werror $(INCLUDE)

$(info mlx_framework Makefile says)
ifeq ($(shell uname), Darwin)
$(info Mac OS detected !)
MLX_PATH = ./minilibx_mac/
LIBS	= -L ./ -L ./libft/ -lm -lft -lmlx -framework OpenGL -framework Appkit
else
$(info $(shell uname) detected !)
MLX_PATH = ./minilibx_xorg/
LIBS	= -L ./ -L $(MLX_PATH) -L ./libft/ -lm -lft -lmlx -lXext -lX11
endif
CFLAGS	= -Ofast -Wall -Wextra -Werror -I ./ -I $(MLX_PATH) -I ./libft/includes/

define colorecho
      @tput setaf 2
      @echo $1
      @tput sgr0
endef

$(NAME): $(OBJ)
	$(call colorecho, Compiling libft)
	make -C ./libft/
	$(call colorecho, Compiling mlx)
	make -C $(MLX_PATH)
	ar -rc $(NAME) $(OBJ)

NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
%.o: %.c
	@echo -n Compiling $@...
	@($(CC) $(CFLAGS) -o $@ -c $<)
	@echo "$(OK_STRING)"

all: $(NAME)
	make -C ./libft/ all
	make -C $(MLX_PATH) all

clean:
	$(call colorecho, Cleaning libft...)
	@make -C ./libft/ clean
	$(call colorecho, Cleaning MLX...)
	@make -C $(MLX_PATH) clean
	rm -rf $(OBJ)

fclean:
	$(call colorecho, Fully cleaning libft...)
	@make -C ./libft/ fclean
	$(call colorecho, Fully cleaning MLX...)
	@make -C $(MLX_PATH) clean
	rm -rf $(OBJ) $(NAME)

re: fclean;
	make
