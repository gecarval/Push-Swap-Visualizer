# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gecarval <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 17:12:20 by gecarval          #+#    #+#              #
#    Updated: 2024/09/24 17:29:23 by gecarval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap_visualizer
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LIBFT = libft.a
MINILIBX = mlx_Linux.a
INCS = -I./includes -I./libft -L./libft ./libft/$(LIBFT) -I./minilibx-linux -lmlx_Linux -L./minilibx-linux -lmlx -L/usr/include/../lib -lXext -lX11 -lm
SRCS = ./bresenham/bresenham.c ./push_swap.c ./visualizer.c ./calls.c ./reads.c ./tools.c ./main.c
OBJS = $(SRCS:.c=.o)
RM = rm -drf

all: $(MINILIBX) $(LIBFT) $(NAME)

run:
	./$(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make all bonus -C libft

$(MINILIBX):
	make -C minilibx-linux

clean:
	$(RM) $(OBJS)
	make clean -C minilibx-linux
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all
