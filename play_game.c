/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2022/12/26 15:03:51 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*iniciando o jogo*/

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	play_game(t_game *game)
{
	int	i;

	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, 1080, 720, "Hello world!");

//	game->img.img_ptr = mlx_xpm_file_to_image(game->mlx, "./textures/tonneau.xpm", &i, &i);
	game->img.img_ptr = mlx_new_image(game->mlx, 1080, 720);
	game->img.data =  (int * )mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.size_l,  &game->img.endian);
//	my_mlx_pixel_put(&game->img, 64, 64, 0x00FF0000);
	int x;
	int y;

	y = -1;
	x = -1;
	while (++y < 720)
	{
		x = -1;
		while (++x < 1080)
		{
			if (x % 2)
			{
				game->img.data[y * 1080 + x] = 0xC00000;
//				my_mlx_pixel_put(&game->img, 64, 64, 0x00FF0000);
			}
			else
				game->img.data[y * 1080 + x] =  0xFFFFFF;
		}

	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.img_ptr, 0, 0);
	mlx_loop(game->mlx);
}
