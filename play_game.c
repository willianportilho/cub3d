/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/18 15:08:40 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Adiciona pixel por pixel nas coordenadas que damos*/
static void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->wdt + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

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
			my_mlx_pixel_put(&game->img, x, y, createRGB(game->c.r, game->c.g, game->c.b));
	}
	--y;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(&game->img, x, y, createRGB(game->f.r, game->f.g, game->f.b));
	}
}

static void	init_player(t_game *game)
{
	game->player.pos[0] = 5;
	game->player.pos[1] = 5;
	game->player.dir[0] = 0;
	game->player.dir[1] = -1;
	game->player.camera_plane[0] = 0.66;
	game->player.camera_plane[1] = 0;
}

static void	calc_ray_dir(float pixel, t_game *game)
{
	float	multiplier;
	float	camera_pixel[2];

	multiplier = 2 * (pixel / WIDTH) - 1;
	camera_pixel[0] = game->player.camera_plane[0] * multiplier;
	camera_pixel[1] = game->player.camera_plane[1] * multiplier;
	game->ray.dir_x = game->player.dir[0] + camera_pixel[0];
	game->ray.dir_y = game->player.dir[1] + camera_pixel[1];
}

void	calc_delta_dist_x_and_y(t_game *game)
{
	if (game->ray.dir_x == 0)
	{
		game->delta.dist_x = 1;
		game->delta.dist_y = 0;
	}
	else
	{
		if (game->ray.dir_y)
		{
			game->delta.dist_x = 1 / game->ray.dir_x;
			if (game->delta.dist_x < 0)
				game->delta.dist_x *= -1;
		}
	}
	if (game->ray.dir_y == 0)
	{
		game->delta.dist_x = 0;
		game->delta.dist_y = 1;
	}
	else
	{
		if (game->ray.dir_x)
		{
			game->delta.dist_y = 1 / game->ray.dir_y;
			if (game->delta.dist_y < 0)
				game->delta.dist_y *= -1;
		}
	}
}

void	calc_dist_to_side_x_and_y(t_game *game)
{
	game->dda.map_pos[0] = (int)game->player.pos[0];
	game->dda.map_pos[1] = (int)game->player.pos[1];
	if (game->ray.dir_x < 0)
	{
		game->dist.side_x = (game->player.pos[0] - (float)game->dda.map_pos[0]) * game->delta.dist_x;
		game->dda.step_x = -1;
	}
	else
	{
		game->dist.side_x = ((float)game->dda.map_pos[0] + 1.0 - game->player.pos[0]) * game->delta.dist_x;
		game->dda.step_x = 1;
	}
	if (game->ray.dir_y < 0)
	{
		game->dist.side_y = (game->player.pos[1] - (float)game->dda.map_pos[1]) * game->delta.dist_y;
		game->dda.step_y = -1;
	}
	else
	{
		game->dist.side_y = ((float)game->dda.map_pos[1] + 1.0 - game->player.pos[1]) * game->delta.dist_y;
		game->dda.step_y = 1;
	}
}

void	dda_find_wall(t_game *game)
{
	int		hit;

	hit = FALSE;
	game->dda.line_size_x = game->dist.side_x;
	game->dda.line_size_y = game->dist.side_y;
	game->dda.wall_map_pos_x = game->dda.map_pos[0];
	game->dda.wall_map_pos_y = game->dda.map_pos[1];
	while (hit == FALSE)
	{
		if (game->dda.line_size_x < game->dda.line_size_y)
		{
			game->dda.wall_map_pos_x += game->dda.step_x;
			game->dda.line_size_x += game->delta.dist_x;
			game->dda.hit_side = 0;
		}
		else
		{
			game->dda.wall_map_pos_y += game->dda.step_y;
			game->dda.line_size_y += game->delta.dist_y;
			game->dda.hit_side = 1;
		}
		if (game->map[(int)game->dda.wall_map_pos_x][(int)game->dda.wall_map_pos_y] > '0')
			hit = TRUE;
	}
}

void	calc_perpendicular_distance(t_game *game)
{
	if (game->dda.hit_side == 0)
	{
		game->dda.perpendicular_ray = (game->dda.wall_map_pos_x - game->player.pos[0] + ((1 - game->dda.step_x) / 2));
		if (game->dda.perpendicular_ray < 0)
			game->dda.perpendicular_ray *= -1;
		game->dda.perpendicular_ray /= game->ray.dir_x;
	}
	else
	{
		game->dda.perpendicular_ray = (game->dda.wall_map_pos_y - game->player.pos[1] + ((1 - game->dda.step_y) / 2));
		if (game->dda.perpendicular_ray < 0)
			game->dda.perpendicular_ray *= -1;
		game->dda.perpendicular_ray /= game->ray.dir_y;
	}
}

void	calc_size_lines_and_print(int pixel, t_game *game)
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

int	ft_close(t_game *game) // fecha o jogo vai pra exit_utils depois
{
	printf("Bye bye\n");
//	mlx_destroy_window(game->mlx, game->window);
	clean_exit(game);
	return (1);
}

int	game_play(t_game *game)
{
	float	pixel;

	pixel = -1;
	fill_background(game);
	while (++pixel < WIDTH)
	{
		calc_ray_dir(pixel, game);
		calc_delta_dist_x_and_y(game);
		calc_dist_to_side_x_and_y(game);
		dda_find_wall(game);
		calc_perpendicular_distance(game);
		calc_size_lines_and_print(pixel, game);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.img_ptr, 0, 0);
	return (0);
}

void	play_game(t_game *game)
{
	game->mlx = mlx_init();
	get_texture(game);
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.wdt, &game->img.endian);
	game->img.data = (int *)mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.size_l, &game->img.endian);
	init_player(game);
	mlx_loop_hook(game->mlx, &game_play, game); //roda o jogo em loop
	mlx_key_hook(game->window, &ft_key, game); // verifica tecla foi pressionada
	mlx_hook(game->window, 33, 1L << 17, ft_close, game); // Clicar no X =ESC
	mlx_loop(game->mlx);
}
