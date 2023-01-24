/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:39:20 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/24 17:47:23 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
	takes only the map, without elements. the start variable is incremented
	until finds 6 elements acronyms (WE, EA, NO, SO, F and C). if not finds,
	returns a error.
*/
static void	get_only_map(t_game *game)
{
	int	i;
	int	size;
	int	start;

	i = -1;
	start = 0;
	while (start < 8 && game->map[++i])
	{
		size = ft_strlen(game->map[i]) - 1;
		if ((ft_strnstr(game->map[i], "WE", size) != 0)
			|| (ft_strnstr(game->map[i], "EA", size) != 0)
			|| (ft_strnstr(game->map[i], "NO", size) != 0)
			|| (ft_strnstr(game->map[i], "SO", size) != 0)
			|| (ft_strnstr(game->map[i], "F", size) != 0)
			|| (ft_strnstr(game->map[i], "C", size) != 0)
			|| (ft_strnstr(game->map[i], "S1", size) != 0) //bonus
			|| (ft_strnstr(game->map[i], "S2", size) != 0))
			start++;
	}
	if (start < 8)
		map_error("needed 8 elements", game);
	game->map = ft_str_arrayndup_free(start, game->map);
	if (!game->map)
		return (destroy_pointers_char(game->map));
}

static void	fill_new_map(int greather_line, char **normalized_map, t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		normalized_map[i] = (char *)malloc((greather_line + 1) * sizeof(char));
		if (normalized_map[i] == NULL)
			exit (EXIT_FAILURE);
		while (game->map[i][++j])
			normalized_map[i][j] = game->map[i][j];
		while (j < greather_line)
			normalized_map[i][j++] = ' ';
		normalized_map[i][j] = '\0';
	}
	destroy_pointers_char(game->map);
	game->map = normalized_map;
}

static void	normalization(t_game *game)
{
	int		i;
	int		greather_line;
	char	**normalized_map;

	i = -1;
	greather_line = 0;
	while (game->map[++i])
	{
		if (greather_line < (int)ft_strlen(game->map[i]))
			greather_line = ft_strlen(game->map[i]);
	}
	normalized_map = malloc((ft_str_arraylen(game->map) + 1) * sizeof(char *));
	if (normalized_map == NULL)
		exit (EXIT_FAILURE);
	normalized_map[i] = NULL;
	fill_new_map(greather_line, normalized_map, game);
}

static void	check_characters(t_game *game)
{
	int	i;
	int	j;
	int	player;

	i = -1;
	player = 0;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (ft_strchr(" 10ENSW2", game->map[i][j]) == NULL)
				map_error("invalid character", game);
			if (ft_strchr("ENSW", game->map[i][j]))
				player++;
		}
	}
	if (player != 1)
		map_error("needed one player (only one is allowed)", game);
}

void	parse_map(t_game *game)
{
	get_only_map(game);
	normalization(game);
	check_characters(game);
	check_break_line(game);
	check_walls_1(game);
	check_walls_2(game);
	check_corners(game);
}
