/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/19 00:22:52 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_texture_2(t_game *game, int wall_start, int wall_end, int i)
{
	int	y;
	int	textuy;
	int	color;

	y = wall_start;
	while (y < wall_end)
	{
		textuy = (int)game->print_textu.texpos & (TILE_SIZE - 1);
		game->print_textu.texpos += game->print_textu.step;
		color = game->textu[game->print_textu.textu_index].img.data[TILE_SIZE
			* textuy + game->print_textu.textux];
			game->img.data[y * WIDTH + i] = color;
		y++;
	}
}

/*lendo a linha que vai ser printada e calculando os tamanhos e coordenas antes
	de atribuir os pixels*/
/*	textu_index; //indice do pixel da textura a ser usado
	wallx; // ponto exato onde o raio atingiu a parede
	textux; // Coordenada x da textura
	step; // cada passo dado é um step que é baseado na altura da linha
	texpos; //posição da textura que vai alterando com cada passo dado*/

void	print_texture(t_game *game, int wall_start, int wall_end, int i)
{
	if (game->dda.hit_side == 0 && game->ray.dir_x >= 0)
		game->print_textu.textu_index = 0;
	if (game->dda.hit_side == 0 && game->ray.dir_x < 0)
		game->print_textu.textu_index = 1;
	if (game->dda.hit_side == 1 && game->ray.dir_y >= 0)
		game->print_textu.textu_index = 2;
	if (game->dda.hit_side == 1 && game->ray.dir_y < 0)
		game->print_textu.textu_index = 3;
	if (game->dda.hit_side == 0)
		game->print_textu.wallx = game->player.pos[1]
			+ game->dda.perpendicular_ray * game->ray.dir_y;
	else
		game->print_textu.wallx = game->player.pos[0]
			+ game->dda.perpendicular_ray * game->ray.dir_x;
	game->print_textu.wallx -= floor(game->print_textu.wallx);
	game->print_textu.textux = (int)(game->print_textu.wallx * (float)
			TILE_SIZE);
	if ((game->dda.hit_side == 0 && game->ray.dir_x > 0)
		|| (game->dda.hit_side == 1 && game->ray.dir_y < 0))
		game->print_textu.textux = TILE_SIZE - game->print_textu.textux - 1;
	game->print_textu.step = 1.0 * TILE_SIZE / game->dda.wall_line_height;
	game->print_textu.texpos = (wall_start - HEIGHT / 2
			+ game->dda.wall_line_height / 2) * game->print_textu.step;
	print_texture_2(game, wall_start, wall_end, i);
}

void	get_texture_2(t_game *game)
{
	game->textu[2].img.img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->we_wall_path, &game->textu[2].img.wdt, &game->textu[2].img
			.hgt);
	if (!game->textu[2].img.img_ptr)
		texture_error("Texture error", game);
	game->textu[2].img.data = (int *)mlx_get_data_addr(game->textu[2].img
			.img_ptr, &game->textu[2].img.bpp, &game->textu[2].img.size_l,
			&game->textu[2].img.endian);
	game->textu[3].img.img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->ea_wall_path, &game->textu[3].img.wdt, &game->textu[3].img
			.hgt);
	if (!game->textu[3].img.img_ptr)
		texture_error("Texture error", game);
	game->textu[3].img.data = (int *)mlx_get_data_addr(game->textu[3].img
			.img_ptr, &game->textu[3].img.bpp, &game->textu[3].img.size_l,
			&game->textu[3].img.endian);
}

/*Salva texturas em um array pra serem lidas posteriormente*/
void	get_texture(t_game *game)
{
	game->textu[0].img.img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->no_wall_path, &game->textu[0].img.wdt, &game->textu[0].img
			.hgt);
	if (!game->textu[0].img.img_ptr)
		texture_error("Texture error", game);
	game->textu[0].img.data = (int *)mlx_get_data_addr(game->textu[0].img
			.img_ptr, &game->textu[0].img.bpp, &game->textu[0].img.size_l,
			&game->textu[0].img.endian);
	game->textu[1].img.img_ptr = mlx_xpm_file_to_image(game->mlx,
			game->so_wall_path, &game->textu[1].img.wdt, &game->textu[1].img
			.hgt);
	if (!game->textu[1].img.img_ptr)
		texture_error("Texture error", game);
	game->textu[1].img.data = (int *)mlx_get_data_addr(game->textu[1].img
			.img_ptr, &game->textu[1].img.bpp, &game->textu[1].img.size_l,
			&game->textu[1].img.endian);
	get_texture_2(game);
}
