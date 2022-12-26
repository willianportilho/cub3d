/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2022/12/25 20:05:26 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*iniciando o jogo*/
void	play_game(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, 1080, 720, "Hello world!");
	game->img.img_ptr = mlx_new_image(game->mlx, 1080, 720);
	game->img.data =  (int * )mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.size_l,  &game->img.endian);

	int x;
	int y;

	y = -1;
	x = -1;
	while (++y < 1080)
	{
		while (++x < 720)
		{
			if (x % 2)
				game->img.data[y * 720 + x] = 0xFFFFFF;
			else
				game->img.data[y * 720 + x] = 0;
		}

	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.img_ptr, 0, 0);
	mlx_loop(game->mlx);
}
