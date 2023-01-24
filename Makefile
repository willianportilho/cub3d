# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 22:45:46 by acosta-a          #+#    #+#              #
#    Updated: 2023/01/24 16:40:35 by wportilh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_B = cub3D_bonus

# Compilation Flags#
FLAGS = -g3 -Werror -Wextra -Wall
MLX_FLAGS = -lm -lbsd -lmlx -lXext -lX11
RM = rm -rf

#Objects
SOURCES = cub3d.c exit_utils.c parse_settings.c parse_utils.c parse_map_1.c \
parse_map_2.c play_game.c play_game_2.c print_texture.c move.c game_utils.c \
exit_utils_mlx.c colision.c

#Objects bonus
SOURCES_B = cub3d_bonus.c exit_utils_bonus.c parse_settings_bonus.c parse_settings_2_bonus.c \
parse_utils_bonus.c parse_map_1_bonus.c parse_map_2_bonus.c play_game_bonus.c play_game_2_bonus.c \
print_texture_bonus.c move_bonus.c game_utils_bonus.c exit_utils_mlx_bonus.c colision_bonus.c sprite_bonus.c \
sprite_init_bonus.c

SRC_PATH =	mandatory_part/
OBJ_PATH =	obj/
SRCS =	${addprefix ${SRC_PATH}, ${SOURCES}}
OBJS =	$(addprefix $(OBJ_PATH), $(SOURCES:.c=.o))

SRC_B_PATH =	bonus_part/
OBJ_B_PATH =	obj_bonus/
SRCS_B =	${addprefix ${SRC_B_PATH}, ${SOURCES_B}}
OBJS_B =	$(addprefix $(OBJ_B_PATH), $(SOURCES_B:.c=.o))

#HEADER = /include#
LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft
MLX = ./minilibx-linux/libmlx.a
MLX_PATH = ./minilibx-linux

#HEADER = /include#
LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft
MLX = ./minilibx-linux/libmlx.a
MLX_PATH = ./minilibx-linux

$(MLX):
	make -C $(MLX_PATH)

$(LIBFT):
	make -C $(LIBFT_PATH)
	
all: $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
	gcc $(FLAGS) -o $(NAME) $(OBJS) -L $(LIBFT_PATH) -L $(MLX_PATH) -lft $(MLX_FLAGS)

${OBJ_PATH}%.o:	$(SRC_PATH)%.c
				@mkdir -p obj
				@${CC} ${CFLAGS} -c $< -o $@

bonus:	$(NAME_B)

$(NAME_B):	$(OBJS_B) $(LIBFT) $(MLX)
			gcc $(FLAGS) -o $(NAME_B) $(OBJS_B) -L $(LIBFT_PATH) -L $(MLX_PATH) -lft $(MLX_FLAGS)

${OBJ_B_PATH}%.o:	$(SRC_B_PATH)%.c
				@mkdir -p obj_bonus
				@${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) $(OBJ_PATH) $(OBJ_B_PATH)
	make clean -C ${LIBFT_PATH}
	make clean -C ${MLX_PATH}

fclean: clean
	$(RM) $(NAME) $(NAME_B)
	make fclean -C ${LIBFT_PATH}

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus mlx
