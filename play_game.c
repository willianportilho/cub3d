/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/23 22:22:59 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Adiciona um fundo à tela (preenche a metade da tela)*/
static void	fill_background(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < (HEIGHT / 2))
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(&game->img, x, y,
				create_rgb(game->c.r, game->c.g, game->c.b));
	}
	--y;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(&game->img, x, y,
				create_rgb(game->f.r, game->f.g, game->f.b));
	}
}

static void	init_player(t_game *game)
{
	int	x;
	int	y;

	game->player.dir[0] = 0;
	game->player.dir[1] = -1;
	game->player.camera_plane[0] = 0.66;
	game->player.camera_plane[1] = 0;
	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (ft_isalpha(game->map[y][x]))
			{
				game->player.pos[0] = (float)x + 0.5;
				game->player.pos[1] = (float)y + 0.5;
				return ;
			}
		}
	}
}

static void	get_size_lines_and_print(int pixel, t_game *game)
{
	int	line_start_y;
	int	line_end_y;

	game->dda.wall_line_height = HEIGHT / game->dda.perpendicular_ray;
	if (game->dda.wall_line_height < 0)
		game->dda.wall_line_height *= -1;
	line_start_y = HEIGHT / 2 - game->dda.wall_line_height / 2;
	line_end_y = HEIGHT / 2 + game->dda.wall_line_height / 2;
	if (line_start_y < 0)
		line_start_y = 0;
	if (line_end_y > HEIGHT)
		line_end_y = HEIGHT - 1;
	print_texture(game, line_start_y, line_end_y, (int)pixel);
}

int	load_game(t_game *game)
{
	float	pixel;

	pixel = -1;
	fill_background(game);
	while (++pixel < WIDTH)
	{
		calc_ray_dir(pixel, game);
		calc_delta_dist_x_and_y(game);
		calc_dist_to_side_x_and_y(game);
		calc_dda_find_wall(game);
		calc_perpendicular_distance(game);
		get_size_lines_and_print(pixel, game);
		game->spr.zbuffer[(int)pixel] = game->dda.perpendicular_ray; //bonus
	}
	sprite_main(game); //bonus
	mlx_put_image_to_window(game->mlx, game->window, game->img.img_ptr, 0, 0);
	return (0);
}

/*	load game: runs the game; ft_key: right and left arrows (rotation) and
	WSAD (up, down, left, right); ft_close: press 'X' or ESC, closes the game*/
void	play_game(t_game *game)
{
	game->mlx = mlx_init();
	get_texture(game);
	get_sprite_texture(game); //bonus
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.wdt, &game->img.endian);
	game->img.data = (int *)mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.size_l, &game->img.endian);
	init_player(game);
	mlx_loop_hook(game->mlx, &load_game, game);
	mlx_hook(game->window, 2, 1L << 0, ft_key, game);
	mlx_hook(game->window, 33, 1L << 17, ft_close, game);
	mlx_loop(game->mlx);
}
