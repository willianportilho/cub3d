/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:30:52 by acosta-a          #+#    #+#             */
/*   Updated: 2022/12/21 19:03:31 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_settings(t_game *game, char **map)
{
	if(ft_strncmp())
}


void	parse_settings(t_game *game, char **map)
{
	int		i;
	int		j;

	i = -1;
	while (map[i++])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == 'C')
				printf("C %d\n", i);
			if (map[i][j] == 'F')
				printf("F %d\n", i);
			j++;
		}
	}
	printf("%d", game->x);
}

