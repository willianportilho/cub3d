/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 09:00:06 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/22 18:48:41 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_sprite_pos(t_game *game) // bonus
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '2')
			{
				game->spr_pos[k].x = (float)j + 0.5;
				game->spr_pos[k].y = (float)i + 0.5;
				k++;
			}
		}
	}
}

void	init_sprite(t_game *game) // bonus
{
	int	i;
	int	j;
	int	k;

	i = -1;
	game->spr.count = 0;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '2')
				game->spr.count++;
		}
	}
	game->spr_pos = (t_spr_pos *)malloc(sizeof(t_spr_pos) * game->spr.count);
	game->spr.order = (int *)malloc(sizeof(int) * game->spr.count);
	game->spr.dist = (float *)malloc(sizeof(float) * game->spr.count);
	game->spr.zbuffer = (float *)malloc(sizeof(float) * WIDTH);
	init_sprite_pos(game);
}
