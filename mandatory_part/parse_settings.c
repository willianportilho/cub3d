/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:30:52 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/23 22:25:48 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	takes the number of colors from C, and saves in a rgb vector
	(red, green and blue)
*/
static void	get_c_colors(t_game *game, char *map_line)
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
static void	get_f_colors(t_game *game, char *map_line)
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

static int	get_settings_2(t_game *game, char *map_line)
{
	if (map_line && !ft_strncmp(map_line, "F", 1) && !game->f_inputs)
	{
		game->f_inputs = ft_substr(map_line, 1, ft_strlen(map_line) - 1);
		get_f_colors(game, map_line);
		game->settings_count += 17;
		return (1);
	}
	if (map_line && !ft_strncmp(map_line, "C", 1) && !game->c_inputs)
	{
		game->c_inputs = ft_substr(map_line, 1, ft_strlen(map_line) - 1);
		get_c_colors(game, map_line);
		game->settings_count += 19;
		return (1);
	}
	if (map_line && !ft_strncmp(map_line, "EA", 2) && !game->ea_wall_path)
	{
		game->ea_wall_path = ft_substr(map_line, 2, ft_strlen(map_line) - 2);
		game->settings_count += 13;
		return (1);
	}
	return (0);
}

/*
	takes all the path written after NO, EA, SO ,WE , F and C
*/
static int	get_settings(t_game *game, char *map_line)
{
	if (map_line && !ft_strncmp(map_line, "NO", 2) && !game->no_wall_path)
	{
		game->no_wall_path = ft_substr(map_line, 2, ft_strlen(map_line) - 2);
		game->settings_count += 5;
		return (1);
	}
	if (map_line && !ft_strncmp(map_line, "SO", 2) && !game->so_wall_path)
	{
		game->so_wall_path = ft_substr(map_line, 2, ft_strlen(map_line) - 2);
		game->settings_count += 7;
		return (1);
	}
	if (map_line && !ft_strncmp(map_line, "WE", 2) && !game->we_wall_path)
	{
		game->we_wall_path = ft_substr(map_line, 2, ft_strlen(map_line) - 2);
		game->settings_count += 11;
		return (1);
	}
	if (get_settings_2(game, map_line) == 1)
		return (1);
	return (0);
}

void	parse_settings(t_game *game, char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i] && map[i][j])
		{
			if (i < 6)
				remove_space(map[i]);
			if (get_settings(game, map[i]) == 1)
				i++;
			j++;
		}
	}
	if (game->settings_count != 72)
		map_missing_error("Map must have 6 valid settings", game);
	if (game->f.r > 255 || game->f.g > 255 || game->f.b > 255 || game->c.r > 255
		|| game->c.g > 255 || game->c.b > 255 || game->f.r < 0
		|| game->f.g < 0 || game->f.b < 0 || game->c.r < 0
		|| game->c.g < 0 || game->c.b < 0)
		map_error("Colors range must be from 0 to 255", game);
}
