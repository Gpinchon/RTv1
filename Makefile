# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/24 18:08:48 by gpinchon          #+#    #+#              #
#    Updated: 2016/10/23 18:56:36 by gpinchon         ###   ########.fr        #
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
BASE_DIR = ./libs/

$(info RT Makefile says)
ifeq ($(shell uname), Darwin)
 $(info Mac OS detected !)
 SDL_PATH = $(BASE_DIR)sdl_framework/
 SDL_LIBS = -lsdl_framework -framework OpenGL -framework Appkit
else
 $(info $(shell uname) detected !)
 SDL_PATH = $(BASE_DIR)sdl_framework/
 SDL_LIBS = -lsdl_framework -lSDL2main -lSDL2 -lGL
endif

LIBS	= -L $(BASE_DIR) -L $(BASE_DIR)libft/ -L $(BASE_DIR)vml/ -L $(SDL_PATH)includes/ -lm -lvml -lsdl_framework -lft $(SDL_LIBS)
INCLUDE = -I ./includes/ -I $(BASE_DIR) -I $(BASE_DIR)libft/includes/ -I $(BASE_DIR)vml/include -I $(BASE_DIR)sdl_framework -I $(SDL_PATH)
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
	$(call colorecho, Compiling sdl_framework lib...)
	@make -s -C $(BASE_DIR)sdl_framework/
	$(call colorecho, Compiling vml lib...)
	@make -s -C $(BASE_DIR)vml/
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
	$(call colorecho, Cleaning sdl_framework lib...)
	@make -C $(SDL_PATH) clean
	$(call colorecho, Cleaning vml lib...)
	@make -C $(BASE_DIR)vml/ clean

fclean:
	$(call colorecho, Fully cleaning RT)
	rm -f $(OBJ) $(NAME)
	$(call colorecho, Fully cleaning sdl_framework lib...)
	@make -C $(SDL_PATH) fclean
	$(call colorecho, Fully cleaning vml lib...)
	@make -C $(BASE_DIR)vml/ fclean

re: fclean
	make

.PHONY: all clean fclean re $(NAME)
