# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siykim <siykim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 19:43:51 by siykim            #+#    #+#              #
#    Updated: 2023/05/17 12:49:48 by siykim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	srcs/main.c \
			srcs/parse.c \
			srcs/parse_map.c \
			srcs/parse_tools.c \
			srcs/parse_check.c \
			srcs/gnl.c \
			srcs/key.c \
			srcs/display.c \
			srcs/display_out.c \
			srcs/tools.c \
			srcs/tools2.c 

OBJS	=	$(SRCS:.c=.o)

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) -L mlx -lmlx -framework OpenGL -framework AppKit $^  -g -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)
	rm -f bitmap.bmp

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re