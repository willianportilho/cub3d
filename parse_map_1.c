/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:39:20 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/23 20:15:16 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Pega somente o mapa, sem os elementos. Essa variável start é incrementada
até achar as 6 correspondências com strnstr. Se não acha, retorna erro.
  Com start, consigo saber de qual index eu começo a copiar o mapa*/
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
			|| (ft_strnstr(game->map[i], "S1", size) != 0)//alterei
			|| (ft_strnstr(game->map[i], "S2", size) != 0))//alterei
			start++;
	}
	if (start < 8)//alterei
		map_error("needed 8 elements", game);//alterei
	game->map = ft_str_arrayndup_free(start, game->map); /* Aqui eu coloco
	 manualmente a posição do mapa. Depois podemos mudar isso.*/
	if (!game->map)
		return (destroy_pointers_char(game->map)); /* Estou limpando aqui por
		 enquanto, mas depois podemos unir na função clean se eu incluir
		  game->map no t_game*/
}

static void	normalization(t_game *game)
{
	int		i;
	int		j;
	int		greather_line;
	char	**normalized_map;

	i = -1;
	greather_line = 0;
	while (game->map[++i])
	{
		if (greather_line < ft_strlen(game->map[i]))
			greather_line = ft_strlen(game->map[i]);
	}
	normalized_map = (char **)malloc((ft_str_arraylen(game->map) + 1)
		* sizeof(char *));
	if (normalized_map == NULL)
		exit (EXIT_FAILURE);
	normalized_map[i] = NULL;
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
			if (ft_strchr(" 10ENSW2", game->map[i][j]) == NULL) //alterado bonus
				map_error("invalid character", game);
			if (ft_strchr("ENSW", game->map[i][j]))
				player++;
		}
	}
	if (player != 1)
		map_error("needed one player (only one is allowed)", game);
}

void	check_break_line(t_game *game)
{
	int	i;
	int	elements;

	i = -1;
	elements = 0;
	while ((game->single_line_map[++i]) && (elements < 8))//alterei
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
