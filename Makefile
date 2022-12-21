# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 22:45:46 by acosta-a          #+#    #+#              #
#    Updated: 2022/12/21 18:32:19 by acosta-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# Compilation #
SRCS = cub3D.c exit_utils.c parse_settings.c
FLAGS = -g -Werror -Wextra -Wall
RM = rm -rf
OBJS = ${SRCS:.c=.o}

#HEADER = /include#
LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft

$(NAME) : $(OBJS)
	make -C ${LIBFT_PATH}
	gcc  $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C ${LIBFT_PATH}

fclean: clean
	$(RM) $(NAME)
	make fclean -C ${LIBFT_PATH}

re: fclean all clean

.PHONY: clean fclean re
