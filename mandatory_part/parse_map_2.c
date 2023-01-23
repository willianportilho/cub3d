/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:18:14 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/23 20:38:33 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Aqui estou testando uma outra abordagem que parece melhor, para checar
se ' ' espaços estão ao lado de um caratere proibido "0ENSW"
   Os espaços só podem ficar ao lado de espaços ' ' e muros '1'
   Por enquanto, eu tirei o "!= NULL" das checagens para caber na norma
(80 colunas), mas depois vejo se consigo otimizar para ficar mais legível*/
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
					// Acho que vou fazer um define com essas mensagens depois
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

/*Essa fução checa se as linhas e colunas no index 0 e último index antes do
'\0' são diferentes de espaço ' ' ou um '1'*/
void	check_walls_2(t_game *game)
{
	int	i;
	int	j;
	int	size;

	i = -1;
	j = -1;
	size = ft_strlen(game->map[0]);
	while (game->map[++i]) // checa linhas
	{
		if ((ft_strchr("0ENSW", game->map[i][0])) // index 0
		|| (ft_strchr("0ENSW", game->map[i][size - 1]))) // último index
			map_error("invalid format: needed '1' around the map", game);
	}
	while (++j < size) // checa colunas
	{
		if ((ft_strchr("0ENSW", game->map[0][j])) // index 0
		|| (ft_strchr("0ENSW", game->map[ft_str_arraylen(game->map) - 1][j])))
		// último index
			map_error("invalid format: needed '1' around the map", game);
	}
}

/* Checa as condições dos espaços com 0ENSW*/
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
		if ((i > 1) && (ft_strchr("0ENSW", game->map[i - 1][j + 1])))
			map_error("invalid format4: needed 1 around the map", game);
	}
}

/*
	Essa função checa se alguma quina que tenha espaço coincide com 0ENSW

	ex: 1111
		11 1
		1011 (esse 0 é errado nesse cenário)
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
