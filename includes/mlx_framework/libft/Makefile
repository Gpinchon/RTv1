# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/27 16:34:53 by gpinchon          #+#    #+#              #
#    Updated: 2016/07/02 13:00:52 by gpinchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
SRC		=	srcs/ft_bzero.c			\
			srcs/ft_isdigit.c		\
			srcs/ft_memccpy.c		\
			srcs/ft_memchr.c		\
			srcs/ft_memcmp.c		\
			srcs/ft_memcpy.c		\
			srcs/ft_memset.c		\
			srcs/ft_strcat.c		\
			srcs/ft_strchr.c		\
			srcs/ft_strcpy.c		\
			srcs/ft_strdup.c		\
			srcs/ft_strlen.c		\
			srcs/ft_strncat.c		\
			srcs/ft_strncpy.c		\
			srcs/ft_strnstr.c		\
			srcs/ft_strrchr.c		\
			srcs/ft_strstr.c		\
			srcs/ft_strcmp.c		\
			srcs/ft_strncmp.c		\
			srcs/ft_isdigit.c		\
			srcs/ft_atoi.c			\
			srcs/ft_isalpha.c		\
			srcs/ft_isalnum.c		\
			srcs/ft_isascii.c		\
			srcs/ft_isprint.c		\
			srcs/ft_toupper.c		\
			srcs/ft_tolower.c		\
			srcs/ft_memalloc.c		\
			srcs/ft_memdel.c		\
			srcs/ft_strnew.c		\
			srcs/ft_strdel.c		\
			srcs/ft_strclr.c		\
			srcs/ft_striter.c		\
			srcs/ft_striteri.c		\
			srcs/ft_strmap.c		\
			srcs/ft_strmapi.c		\
			srcs/ft_strequ.c		\
			srcs/ft_strnequ.c		\
			srcs/ft_strsub.c		\
			srcs/ft_strjoin.c		\
			srcs/ft_strtrim.c		\
			srcs/ft_putchar.c		\
			srcs/ft_putstr.c		\
			srcs/ft_putendl.c		\
			srcs/ft_putnbr.c		\
			srcs/ft_putchar_fd.c	\
			srcs/ft_putstr_fd.c		\
			srcs/ft_putendl_fd.c	\
			srcs/ft_putnbr_fd.c		\
			srcs/ft_itoa.c			\
			srcs/ft_strsplit.c		\
			srcs/ft_memmove.c		\
			srcs/ft_strlcat.c		\
			srcs/ft_strrev.c		\
			srcs/ft_charswap.c		\
			srcs/ft_intswap.c		\
			srcs/get_next_line.c	\
			srcs/clamp.c			\
			srcs/cycle_float.c		\
			srcs/cycle_int.c		\
			srcs/countchar.c		\
			srcs/wordcount.c		\
			srcs/file_to_str.c		\
			srcs/ft_lstnew.c		\
			srcs/ft_lstdelone.c		\
			srcs/ft_lstdel.c		\
			srcs/ft_lstadd.c		\
			srcs/ft_lstiter.c		\
			srcs/ft_lstmap.c

OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Ofast -Wall -Wextra -Werror


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
