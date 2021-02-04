# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/03 22:06:23 by hasv              #+#    #+#              #
#    Updated: 2021/02/04 03:25:38 by hasv             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		miniRT

CFILE =		srcs/main.c\
			srcs/render.c\
			srcs/sphere.c\
			srcs/utils.c\
			srcs/parser.c\
			srcs/get_next_line.c\
			srcs/get_next_line_utils.c\
			srcs/ft_split.c\
			srcs/lights_list.c\
			srcs/objects_list.c\

INCLUDES =	includes/

MLX_FLAGS =	-Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME):
		@echo miniRT start.
		@export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0
		@export DISPLAY=localhost:0.0
		gcc -g -Wall -Wextra -Werror -I $(INCLUDES) $(CFILE) $(MLX_FLAGS) -o $(NAME)
		@echo miniRT compiled!

clean:
		@rm -rf $(NAME)
		@echo Cleaned miniRT output file!

fclean: clean

re: clean all