# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suroh <suroh@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/26 12:32:36 by suroh             #+#    #+#              #
#    Updated: 2024/10/26 14:24:34 by suroh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol

SRC	= main.c \
	init.c \
	render.c \
	events.c \
	math_utils.c \
	string_utils.c

OBJ	= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJDIR	= ./obj_files
CFLAGS	= -Wextra -Wall -Werror
CC	= cc
MLX	= ./minilibx-linux/
MLX_LNK	= -L $(MLX) -lmlx -lXext -lX11 -lm
MLX_INC = -I $(MLX)
MLX_LIB	= ./minilibx-linux/libmlx_Linux.a

all: obj $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INC) -I ./ -o $@ -c $<

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LNK) -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all
