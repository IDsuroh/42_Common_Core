# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 21:12:22 by suroh             #+#    #+#              #
#    Updated: 2024/11/12 22:19:11 by suroh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = pipex.c utils.c 
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
	@echo "\033[35mCleaned Object Files."

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB)
	@find . -type f ! -name "*.c" ! -name "*.h" ! -name "Makefile" ! -path "./libft/*" -exec rm -f {} +
	@find . -type d ! -path "./libft" ! -path "." -exec rm -rf {} +
	@echo "\033[34mCleaned Everything."

re: fclean all

.PHONY: all clean fclean re
