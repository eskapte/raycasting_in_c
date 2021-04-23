# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhawick <lhawick@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/11 15:19:49 by lhawick           #+#    #+#              #
#    Updated: 2021/03/11 15:19:49 by lhawick          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	cub3D

CC =	gcc

SRC =	src/ft_main.c gnl/get_next_line.c gnl/get_next_line_utils.c \
		src/cub_utils.c src/ft_parcer.c src/ft_errors.c src/ft_render.c \
		src/ft_rays.c src/ft_player.c src/ft_drawing.c src/ft_sprites.c \
		src/textures_parser.c src/texture_parser2.c

OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I. -g -O3 -ffast-math

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C libft/
	make -C mlx_linux/
	mv mlx_linux/libmlx.a ./
	#$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./libft -lft -Lmlx -lmlx -framework OpenGL -framework Appkit
	# make clean
	 $(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibmlx -lmlx -lX11 -lbsd \
	 											-lm -lXext ./libft/libft.a

clean:
	rm -f $(OBJS)
	make clean -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: 
	make re -C libft/
	make fclean
	make

norm:
	norminette $(SRC) libft/

.phony:
	all clean fclean re norm