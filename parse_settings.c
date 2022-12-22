/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:30:52 by acosta-a          #+#    #+#             */
/*   Updated: 2022/12/22 00:28:38 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_settings_2(t_game *game, char *map_line)
{
	if (map_line && !ft_strncmp(map_line, "F", 1))
	{
		game->f_inputs = ft_substr(map_line, 1,  ft_strlen(map_line) - 1);
		printf("%s", game->f_inputs);
		return(1);
	}
	if (map_line && !ft_strncmp(map_line, "C", 1))
	{
		game->c_inputs = ft_substr(map_line, 1,  ft_strlen(map_line) - 1);
		return(1);
	}
	return (0);
}
//função que pega tudo que vem escrito após o NO, EA, SO ,WE , F e C  
int	get_settings(t_game *game, char *map_line)
{
	if (map_line && !ft_strncmp(map_line, "NO", 2))
	{
		game->no_wall_path = ft_substr(map_line, 2,  ft_strlen(map_line) - 2);
		return(1);
	}
	if (map_line && !ft_strncmp(map_line, "SO", 2))
	{
		game->so_wall_path = ft_substr(map_line, 2,  ft_strlen(map_line) - 2);
		return(1);
	}
	if (map_line && !ft_strncmp(map_line, "WE", 2))
	{
		game->we_wall_path = ft_substr(map_line, 2,  ft_strlen(map_line) - 2);
		return(1);
	}
	if (map_line && !ft_strncmp(map_line, "EA", 2))
	{
		game->ea_wall_path = ft_substr(map_line, 2,  ft_strlen(map_line) - 2);
		return(1);
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
	while (map[i++])
	{
		j = 0;
		while (map[i] && map[i][j])
		{
			if (get_settings(game, map[i]) == 1)
				i++;
			j++;
		}
	}
	printf("teste\n");
}
