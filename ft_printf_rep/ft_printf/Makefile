NAME = libftprintf.a

SRC =	ft_printf.c ft_printf_charstr.c ft_printf_ptr.c ft_printf_nbr.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wextra -Wall -Werror

CC = cc

all: $(NAME)

$(NAME): $(OBJ)
	@ar crs $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ) $(NAME)

re: fclean all

.PHONY: all clean fclean re