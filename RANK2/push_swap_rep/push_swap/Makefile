# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suroh <suroh@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 18:06:45 by suroh             #+#    #+#              #
#    Updated: 2024/12/03 22:33:09 by suroh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= push_swap

SRC 	= com_pushes.c com_push_swap.c com_push_swap_utils.c com_rev_rotates.c \
		com_rotates.c com_swaps.c error_commands.c main.c push_swap_init.c \
		sort_three_algo.c stack_init.c stack_utils.c

OBJ		= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJDIR	= ./obj_files
CC 		= cc
CFLAGS 	= -Wall -Werror -Wextra
LIB		= ./libft/
LIBFT	= ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@echo "\033[33m------Compiling LIBFT------"
		@$(CC) $(OBJ) $(LIBFT) -o $(NAME)
		@echo "\033[32m------Compilation Complete------"

$(LIBFT):
		@make makeall -C $(LIB)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@rm -rf $(OBJDIR)
		@echo "\033[35mCleaned Object Files."

fclean: clean
		@rm -rf $(NAME)
		@make fclean -C $(LIB)
		@find . -type f ! -name "push_swap_test_linux.sh" ! -name "*.c" ! -name "*.h" ! -name "Makefile" ! -name "checker_linux" ! -path "./libft/*" -exec rm -f {} +
		@find . -type d ! -path "./libft" ! -path "." -exec rm -rf {} +
		@echo "\033[34mCleaned Everything."

re: fclean all

.PHONY: all clean fclean re
