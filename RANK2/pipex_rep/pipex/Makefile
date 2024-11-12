# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 21:12:22 by suroh             #+#    #+#              #
#    Updated: 2024/11/12 19:08:41 by suroh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = (c files)
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJDIR = ./obj_files
LIB = ./libft/
LIBFT = ./libft/libft.a

all: obj $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	@echo "\033[33m------Compiling LIBFT------"
	@make reall -C $(LIB)
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[32m------Compilation Complete------"

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "Cleaned Object Files."

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB)
	@echo "Cleaned Everything."

re: fclean all

.PHONY: all clean fclean re
