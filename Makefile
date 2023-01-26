# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 22:45:46 by acosta-a          #+#    #+#              #
#    Updated: 2023/01/26 14:21:30 by wportilh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#objects
SOURCES =	cub3d.c						\
			colision.c					\
			exit_utils.c				\
			exit_utils_mlx.c			\
			game_utils.c				\
			move.c						\
			play_game.c					\
			play_game_2.c				\
			parse_map_1.c				\
			parse_map_2.c				\
			parse_settings.c			\
			print_texture.c				\
			parse_utils.c

#objects bonus
SOURCES_B = cub3d_bonus.c				\
			colision_bonus.c			\
			exit_utils_bonus.c			\
			exit_utils_mlx_bonus.c		\
			game_utils_bonus.c			\
			move_bonus.c				\
			play_game_bonus.c			\
			play_game_2_bonus.c			\
			parse_map_1_bonus.c			\
			parse_map_2_bonus.c			\
			parse_settings_bonus.c		\
			parse_settings_2_bonus.c	\
			print_texture_bonus.c		\
			parse_utils_bonus.c			\
			sprite_bonus.c				\
			sprite_init_bonus.c

#programm name
NAME = cub3D
NAME_B = cub3D_bonus

#compilation flags
FLAGS = -g3 -Werror -Wextra -Wall
MLX_FLAGS = -lm -lbsd -lmlx -lXext -lX11
RM = rm -rf

#valgrind
VAL =		valgrind --leak-check=full --show-leak-kinds=all

#HEADER
LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft
MLX = ./minilibx_linux/libmlx.a
MLX_PATH = ./minilibx_linux

SRC_PATH =	mandatory_part/
OBJ_PATH =	obj/
SRCS =	${addprefix ${SRC_PATH}, ${SOURCES}}
OBJS =	$(addprefix $(OBJ_PATH), $(SOURCES:.c=.o))

SRC_B_PATH =	bonus_part/
OBJ_B_PATH =	obj_bonus/
SRCS_B =	${addprefix ${SRC_B_PATH}, ${SOURCES_B}}
OBJS_B =	$(addprefix $(OBJ_B_PATH), $(SOURCES_B:.c=.o))
	
all: $(NAME)

$(NAME) : $(MLX) $(LIBFT) $(OBJS)
	gcc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -L$(MLX_PATH) $(MLX_FLAGS)

${OBJ_PATH}%.o:	$(SRC_PATH)%.c
				@mkdir -p obj
				@${CC} ${FLAGS} -c $< -o $@

bonus:	$(NAME_B)

$(NAME_B):	$(MLX) $(LIBFT) $(OBJS_B)
			gcc $(FLAGS) $(OBJS_B) $(LIBFT)  -o $(NAME_B) -L$(MLX_PATH) $(MLX_FLAGS)

${OBJ_B_PATH}%.o:	$(SRC_B_PATH)%.c
				@mkdir -p obj_bonus
				@${CC} ${FLAGS} -c $< -o $@

$(MLX):
			make -C $(MLX_PATH)

$(LIBFT):
			make -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJ_PATH) $(OBJ_B_PATH)
	make clean -C ${LIBFT_PATH}
	make clean -C ${MLX_PATH}

fclean: clean
	$(RM) $(NAME) $(NAME_B)
	make fclean -C ${LIBFT_PATH}

re: fclean all

rebonus: fclean bonus

norm:
					norminette $(SRC_PATH) $(SRC_B_PATH) $(LIBFT_PATH)

.PHONY: all bonus clean fclean re rebonus mlx
