# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/03 22:06:23 by hasv              #+#    #+#              #
#    Updated: 2021/03/08 21:10:09 by hasv             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		miniRT

CFILE =		srcs/main.c\
			srcs/render.c\
			srcs/utils.c\
			srcs/utils2.c\
			srcs/utils3.c\
			srcs/utils4.c\
			srcs/parser.c\
			srcs/parser2.c\
			srcs/parser3.c\
			srcs/parser_utils.c\
			srcs/get_next_line.c\
			srcs/get_next_line_utils.c\
			srcs/ft_split.c\
			srcs/list.c\
			srcs/sphere.c\
			srcs/triangle.c\
			srcs/plane.c\
			srcs/cylinder.c\
			srcs/disc.c\
			srcs/cone.c\
			srcs/memory.c\
			srcs/rotate.c\
			srcs/square.c\
			srcs/window.c\
			srcs/hooks.c\

INCLUDES =	includes/

MLX_FLAGS =	-Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME):
		@echo miniRT start.
		make -C mlx_linux/
		gcc -Wall -Wextra -Werror -I $(INCLUDES) $(CFILE) $(MLX_FLAGS) -o $(NAME) -O3
		@echo miniRT compiled!

clean:
		@rm -rf $(NAME)
		@echo Cleaned miniRT output file!

fclean: clean
		@make -C mlx_linux/ clean
		@echo Everything cleaned!

re: clean all
