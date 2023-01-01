/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2022/12/30 00:23:27 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*iniciando o jogo*/
# define TILE_SIZE 64

void	get_texture_2(t_game *game)
{
	while(game->i < 4)
	{
		if (!game->textu[game->i].img.img_ptr || !game->textu[game->i].img.data)
			print_exit("Error");
		game->i++;

	}
}
//Salva texturas em um array pra serem lidas posteriormente
void	get_texture(t_game *game)
{
	game->textu[0].img.img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->no_wall_path, &game->textu[0].img.wdt, &game->textu[0].img
			.hgt);
	game->textu[0].img.data = (int *)mlx_get_data_addr(game->textu[0].img
			.img_ptr, &game->textu[0].img.bpp, &game->textu[0].img.size_l,
			&game->textu[0].img.endian);
	game->textu[1].img.img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->so_wall_path, &game->textu[1].img.wdt, &game->textu[1].img
			.hgt);
	game->textu[1].img.data = (int *)mlx_get_data_addr(game->textu[1].img
			.img_ptr, &game->textu[1].img.bpp, &game->textu[1].img.size_l,
			&game->textu[1].img.endian);
	game->textu[2].img.img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->we_wall_path, &game->textu[2].img.wdt, &game->textu[2].img
			.hgt);
	game->textu[2].img.data = (int *)mlx_get_data_addr(game->textu[2].img
			.img_ptr, &game->textu[2].img.bpp, &game->textu[2].img.size_l,
			&game->textu[2].img.endian);
	game->textu[3].img.img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->ea_wall_path, &game->textu[3].img.wdt, &game->textu[3].img
			.hgt);
	game->textu[3].img.data = (int *)mlx_get_data_addr(game->textu[3].img
			.img_ptr, &game->textu[3].img.bpp, &game->textu[3].img.size_l,
			&game->textu[3].img.endian);
	get_texture_2(game);
}

void	change_pixel_color(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->textu[0].img.hgt)
	{
		int  x = 0 ;
		while (x < game->textu[0].img.wdt)
		{
			//a cada 64 pixels ele pinta o pixel no sentido vertical
			if  (x % 64 == 0 )
 				game->textu[0].img.data[game->textu[0].img.hgt* y + x]= 0x00FF00 ;
			//a cada 64 pixels ele pinta o pixel no sentido horizontal
			if  (y %  64 == 0 )
				game->textu[0].img.data[game->textu[0].img.wdt* y + x]= 0x00FF00 ;
			x++ ;
 		}
		y++;
	}
}
void	play_game(t_game *game)
{
	int	i;

	game->mlx = mlx_init();
	get_texture(game);
	game->window = mlx_new_window(game->mlx, 1080, 720, "Hello world!");
	game->img.img_ptr = mlx_new_image(game->mlx, 1080, 720);
	game->img.data =  (int * )mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.size_l,  &game->img.endian);
	//essa funçãp faz os desenhos verdes nas texturas de numero 0, criei ela só pra entender que o img.data guarda as cores dos pixels
	change_pixel_color(game);
	//função que imprimi na tela o mapa
	int j;
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->window, game->textu[0].img.img_ptr, j * 64, i * 64);
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->window, game->textu[1].img.img_ptr, j * 64, i * 64);
		}
	}
	mlx_loop(game->mlx);
}
