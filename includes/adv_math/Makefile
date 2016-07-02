# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/27 21:31:31 by gpinchon          #+#    #+#              #
#    Updated: 2016/06/29 13:51:29 by gpinchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libadv_math.a
SRC		=	./src/vector3/new.c	\
			./src/vector3/normalize.c			\
			./src/vector3/rotation.c			\
			./src/vector3/operations.c			\
			./src/vector3/operations2.c			\
			./src/vector3/operations3.c			\
			./src/vector3/scalar_operations.c	\
			./src/float/interpolate.c			\
			./src/float/operations.c			\
			./src/double/operations.c			\
			./src/matrix/initialisation.c		\
			./src/matrix/projection.c			\
			./src/matrix/operations.c			\
			./src/matrix/invert.c			\
			./src/matrix/mat3_operations.c

OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Ofast -Wall -Wextra -Wall


$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
%.o: %.c
	@echo -n Compiling $@...
	@($(CC) $(CFLAGS) -o $@ -c $<)
	@echo "$(OK_STRING)"

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)