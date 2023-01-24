/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings_2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:30:52 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/24 15:21:35 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
	takes the number of colors from C, and saves in a rgb vector
	(red, green and blue)
*/
void	get_c_colors(t_game *game, char *map_line)
{
	int		i;
	int		j;
	char	*color;

	i = 0;
	while (map_line && map_line[i] != ',')
		i++;
	color = ft_substr(map_line, 1, i - 1);
	game->c.r = ft_atoi(color);
	free(color);
	j = i + 1;
	i++;
	while (map_line && map_line[i] != ',')
		i++;
	color = ft_substr(map_line, j, i - j);
	game->c.g = ft_atoi(color);
	free(color);
	j = i;
	while (map_line && map_line[i])
		i++;
	color = ft_substr(map_line, j + 1, i - j);
	game->c.b = ft_atoi(color);
	free(color);
}

/*
	takes the number of colors from F, and saves in a rgb vector
	(red, green and blue)
*/
void	get_f_colors(t_game *game, char *map_line)
{
	int		i;
	int		j;
	char	*color;

	i = 0;
	while (map_line && map_line[i] != ',')
		i++;
	color = ft_substr(map_line, 1, i - 1);
	game->f.r = ft_atoi(color);
	free(color);
	j = i + 1;
	i++;
	while (map_line && map_line[i] != ',')
		i++;
	color = ft_substr(map_line, j, i - j);
	game->f.g = ft_atoi(color);
	free(color);
	j = i;
	while (map_line && map_line[i])
		i++;
	color = ft_substr(map_line, j + 1, i - j);
	game->f.b = ft_atoi(color);
	free(color);
}
