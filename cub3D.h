/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:41:53 by acosta-a          #+#    #+#             */
/*   Updated: 2022/12/22 00:26:28 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <math.h>
# include "libft/libft.h"
/*
typedef struct s_settings
{
}	t_settings;
*/
typedef struct s_game
{
	int				x;
	char			*no_wall_path;
	char			*so_wall_path;
	char			*we_wall_path;
	char			*ea_wall_path;
	char			*f_inputs;
	char			*c_inputs;
	char			**map;
}	t_game;


/*acho bom colocar no header cada função separada pelo nome do arquivo*/
/* cub3D.c*/

/* exit_utils.c*/
void	print_exit(char *input);
void	destroy_pointers_char(char **p);
void	clean_exit(t_game *game);
void	print_vector(char **p);

/* parse_settings.c*/
void	parse_settings(t_game *game, char **map);

/* parse_utils.c*/
char	*remove_space(char *str);

#endif
