# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 22:45:46 by acosta-a          #+#    #+#              #
#    Updated: 2023/01/20 20:03:04 by wportilh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# Compilation Flags#
FLAGS = -g -Werror -Wextra -Wall
MLX_FLAGS = -lm -lbsd -lmlx -lXext -lX11
RM = rm -rf

#Objects
SRCS = cub3D.c exit_utils.c parse_settings.c parse_utils.c parse_map_1.c \
parse_map_2.c play_game.c play_game_2.c print_texture.c move.c game_utils.c \
exit_utils_mlx.c colision.c
OBJ_PATH = obj/
OBJS =	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

#HEADER = /include#
LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft
MLX = ./minilibx-linux/libmlx.a
MLX_PATH = ./minilibx-linux

all: $(NAME)

$(MLX):
	make -C $(MLX_PATH)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
	gcc $(FLAGS) -o $(NAME) $(OBJS) -L $(LIBFT_PATH) -L $(MLX_PATH) -lft $(MLX_FLAGS)

${OBJ_PATH}%.o:	./%.c
				@mkdir -p obj
				@${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) $(OBJ_PATH)
	make clean -C ${LIBFT_PATH}
	make clean -C ${MLX_PATH}

fclean: clean
	$(RM) $(NAME)
	make fclean -C ${LIBFT_PATH}

re: fclean all clean

.PHONY: all clean fclean re mlx
