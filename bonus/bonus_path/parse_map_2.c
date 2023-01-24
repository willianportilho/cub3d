/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:18:14 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/23 23:46:58 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_break_line(t_game *game)
{
	int	i;
	int	elements;

	i = -1;
	elements = 0;
	while ((game->single_line_map[++i]) && (elements < 8))
	{
		if (ft_isalpha(game->single_line_map[i]))
		{
			elements++;
			while (game->single_line_map[i] != '\n')
				i++;
		}
	}
	while ((game->single_line_map[i] == '\n')
		|| (game->single_line_map[i] == ' '))
		i++;
	while (game->single_line_map[i++])
	{
		if ((game->single_line_map[i] == '\n')
			&& (game->single_line_map[i + 1] == '\n'))
			map_error("double break line founded in the map", game);
	}
}

/*	checks if spaces ' ' are next to a invalid character "0ENSW"*/
void	check_walls_1(t_game *game)
{
	int		i;
	int		j;
	char	**arr;

	i = -1;
	arr = game->map;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (arr[i][j] == ' ')
			{
				if ((j > 0) && (ft_strchr("0ENSW", arr[i][j - 1])))
					map_error("invalid format: needed 1 around the map", game);
				if ((arr[i][j + 1]) && (ft_strchr("0ENSW", arr[i][j + 1])))
					map_error("invalid format: needed 1 around the map", game);
				if ((i > 0) && (ft_strchr("0ENSW", arr[i - 1][j])))
					map_error("invalid format: needed 1 around the map", game);
				if ((arr[i + 1]) && (ft_strchr("0ENSW", arr[i + 1][j])))
					map_error("invalid format: needed 1 around the map", game);
			}
		}
	}
}

/*
	checks if rows and columns at index 0 and last index are different from
	space ' ' or '1'
*/
void	check_walls_2(t_game *game)
{
	int	i;
	int	j;
	int	size;

	i = -1;
	j = -1;
	size = ft_strlen(game->map[0]);
	while (game->map[++i])
	{
		if ((ft_strchr("0ENSW", game->map[i][0]))
		|| (ft_strchr("0ENSW", game->map[i][size - 1])))
			map_error("invalid format: needed '1' around the map", game);
	}
	while (++j < size)
	{
		if ((ft_strchr("0ENSW", game->map[0][j]))
		|| (ft_strchr("0ENSW", game->map[ft_str_arraylen(game->map) - 1][j])))
			map_error("invalid format: needed '1' around the map", game);
	}
}

/*
	checks space conditions with "0ENSW"
	ex: 111  (space next 0 is wrong)
		1101
		1001
		1111
*/
static void	check_conditions(int i, int j, t_game *game)
{
	if ((j > 0) && (game->map[i][j - 1] == '1'))
	{
		if ((game->map[i + 1]) && (ft_strchr("0ENSW", game->map[i + 1][j - 1])))
			map_error("invalid format1: needed 1 around the map", game);
		if ((i > 1) && (ft_strchr("0ENSW", game->map[i - 1][j - 1])))
			map_error("invalid format2: needed 1 around the map", game);
	}
	if ((game->map[i][j + 1]) && (game->map[i][j + 1] == '1'))
	{
		if ((game->map[i + 1]) && (ft_strchr("0ENSW", game->map[i + 1][j + 1])))
			map_error("invalid format3: needed 1 around the map", game);
		if ((i > 1) && (ft_strchr("0ENSW2", game->map[i - 1][j + 1])))
			map_error("invalid format4: needed 1 around the map", game);
	}
}

/*
	checks if some corner that containing a space, matches with "0ENSW"
	ex: 1111
		11 1
		1011 (0 and ' ' are wrong)
		1111
*/
void	check_corners(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == ' ')
				check_conditions(i, j, game);
		}
	}
}
