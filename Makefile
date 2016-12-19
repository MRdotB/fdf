# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchaleil <hello@baptistechaleil.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 16:21:36 by bchaleil          #+#    #+#              #
#    Updated: 2016/12/16 19:31:55 by bchaleil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
NAME			=	fdf
FLAGS			=	-Wall -Werror -Wextra -g
LIBFT_PATH		=	libft/
LIBFT			=	$(LIBFT_PATH)libft.a
MLX_PATH		=	mlx/
MLX				=	$(MLX_PATH)libmlx.a
INCLUDES		=	-I ./includes -I ./libft/includes -I ./mlx
SRCS			=	srcs/main.c

OBJS			=	$(SRCS:srcs/%.c=obj/%.o)

all: obj $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(MLX):
	@make -C $(MLX_PATH)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(FLAGS) -o $@ $^ -lXext -lX11 -lm -lbsd

obj:
	@mkdir -p obj

obj/%.o: srcs/%.c
	$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@rm -f $(OBJS)
	@rm -rf obj

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@make -C $(MLX_PATH) fclean

re: fclean all

.PHONY:clean fclean re
