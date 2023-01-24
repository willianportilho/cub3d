/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 09:00:06 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/23 23:38:50 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_sprite_pos(t_game *game)
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

void	init_sprite(t_game *game)
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

void	get_sprite_texture(t_game *game)
{
	game->textu[4].img.img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->s1_path, &game->textu[4].img.wdt, &game->textu[4].img
			.hgt);
	if (!game->textu[4].img.img_ptr)
		texture_error("Texture error", game);
	game->textu[4].img.data = (int *)mlx_get_data_addr(game->textu[4].img
			.img_ptr, &game->textu[4].img.bpp, &game->textu[4].img.size_l,
			&game->textu[4].img.endian);
	game->textu[5].img.img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->s2_path, &game->textu[5].img.wdt, &game->textu[5].img
			.hgt);
	if (!game->textu[5].img.img_ptr)
		texture_error("Texture error", game);
	game->textu[5].img.data = (int *)mlx_get_data_addr(game->textu[5].img
			.img_ptr, &game->textu[5].img.bpp, &game->textu[5].img.size_l,
			&game->textu[5].img.endian);
}
