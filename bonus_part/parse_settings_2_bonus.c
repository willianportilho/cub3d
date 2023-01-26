/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings_2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:30:52 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/25 19:45:48 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
