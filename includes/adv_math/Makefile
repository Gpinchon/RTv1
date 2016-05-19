NAME	= libadv_math.a
SRC		=	./src/vector3/normalize.c			\
			./src/vector3/operations.c			\
			./src/vector3/scalar_operations.c	\
			./src/float/interpolate.c			\
			./src/double/operations.c			\
			./src/matrix/initialisation.c		\
			./src/matrix/projection.c			\
			./src/matrix/operations.c

OBJ		= $(SRC:.c=.o)
	CC		= gcc
	CFLAGS	= -Ofast -Wall -Wextra -Wall


$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)