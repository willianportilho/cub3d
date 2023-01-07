/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/07 12:15:10 by wportilh         ###   ########.fr       */
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
			my_mlx_pixel_put(&game->img, x, y, 0XBEBEFF);
	}
	--y;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(&game->img, x, y, 0X696969);
	}
}

/*		color = 0X8B0000; // se comentar das linhas 308 a 312 e descomentar a linha 313 ele printa com texturas ja
void	calc_size_lines_to_print(t_game *game)
{
	int		i;
	int		color;

	game->print_line.wall_line_height = malloc((WIDTH + 1) * sizeof(float));
	if (!game->print_line.wall_line_height)
		exit (EXIT_FAILURE);
	i = -1;
	while (++i <= WIDTH)
		game->print_line.wall_line_height[i] = HEIGHT / game->dda.perpendicular_ray[i];
	i = -1;
	while (++i <= WIDTH)
	{
		wall_start = (HEIGHT / 2) - (game->print_line.wall_line_height[i] / 2);
		wall_end = (HEIGHT / 2) + (game->print_line.wall_line_height[i] / 2);
		if (wall_start < 0)
			wall_start = 0;
		if (wall_end >= HEIGHT)
			wall_end = HEIGHT - 1;
		if (game->dda.hit_side[i] == 1)
			color = 0XFF0000;
		while (wall_start < wall_end)
		print_texture(game, wall_start, wall_end, i);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.img_ptr, 0, 0);
}
				my_mlx_pixel_put(&game->img, i, wall_start++, color);*/

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
		float	multiplier = 2 * (pixel / WIDTH) - 1;
		float	camera_pixel[2];
		camera_pixel[0] = game->player.camera_plane[0] * multiplier;
		camera_pixel[1] = game->player.camera_plane[1] * multiplier;
		float	ray_dir[2];
		ray_dir[0] = game->player.dir[0] + camera_pixel[0];
		ray_dir[1] = game->player.dir[1] + camera_pixel[1];
		float	delta_dist_x;
		float	delta_dist_y;
		delta_dist_x = 1 / ray_dir[0];
		delta_dist_y = 1 / ray_dir[1];
		if (delta_dist_x < 0)
			delta_dist_x *= -1;
		if (delta_dist_y < 0)
			delta_dist_y *= -1;

		int	map_pos[2];
		map_pos[0] = (int)game->player.pos[0];
		map_pos[1] = (int)game->player.pos[1];

		float	dist_to_side_x;
		float	dist_to_side_y;
		int		step_x;
		int		step_y;
		float	perpendicular_dist;

		if (ray_dir[0] < 0)
		{
			dist_to_side_x = (game->player.pos[0] - (float)map_pos[0]) * delta_dist_x;
			step_x = -1;
		}
		else
		{
			dist_to_side_x = ((float)map_pos[1] + 1 - game->player.pos[1]) * delta_dist_x;
			step_x = 1;
		}
		if (ray_dir[1] < 0)
		{
			dist_to_side_y = (game->player.pos[1] - (float)map_pos[1]) * delta_dist_y;
			step_y = -1;
		}
		else
		{
			dist_to_side_y = ((float)map_pos[1] + 1 - game->player.pos[1]) * delta_dist_y;
			step_y = 1;
		}

		int		hit = FALSE;
		int		hit_side;

		float	dda_line_size_x = dist_to_side_x;
		float	dda_line_size_y = dist_to_side_y;

		float	wall_map_pos[2];
		wall_map_pos[0] = map_pos[0];
		wall_map_pos[1] = map_pos[1];

		while (hit == FALSE)
		{
			if (dda_line_size_x < dda_line_size_y)
			{
				wall_map_pos[0] += step_x;
				dda_line_size_x += delta_dist_x;
				hit_side = 0;
			}
			else
			{
				wall_map_pos[1] += step_y;
				dda_line_size_y += delta_dist_y;
				hit_side = 1;
			}

			if (game->map[(int)wall_map_pos[0]][(int)wall_map_pos[1]] > '0')
				hit = TRUE;
		}

		if (hit_side == 0)
		{
			perpendicular_dist = (wall_map_pos[0] - game->player.pos[0] + ((1 - step_x) / 2));
			if (perpendicular_dist < 0)
				perpendicular_dist *= -1;
			perpendicular_dist /= ray_dir[0];
		}
		else
		{
			perpendicular_dist = (wall_map_pos[1] - game->player.pos[1] + ((1 - step_y) / 2));
			if (perpendicular_dist < 0)
				perpendicular_dist *= -1;
			perpendicular_dist /= ray_dir[1];
		}
		float	wall_line_height = HEIGHT/perpendicular_dist;

		if (wall_line_height < 0)
			wall_line_height *= -1;
		int	line_start_y = HEIGHT / 2 - wall_line_height / 2;
		int	line_end_y = HEIGHT / 2 + wall_line_height / 2;

		if (line_start_y < 0)
			line_start_y = 0;
		if (line_end_y > HEIGHT)
			line_end_y = HEIGHT - 1;
		int		color;
		if (hit_side == 0)
			color = 0X8B0000;
		else
			color = 0XFF0000;

		while (line_start_y < line_end_y)
			my_mlx_pixel_put(&game->img, pixel, line_start_y++, color);
		//print_texture(game, line_start_y, line_end_y, (int)pixel);
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
	game->img.data =  (int *)mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.size_l,  &game->img.endian);
	game->player.pos[0] = 5;
	game->player.pos[1] = 5;
	game->player.dir[0] = 0;
	game->player.dir[1] = -1;
	game->player.camera_plane[0] = 0.66;
	game->player.camera_plane[1] = 0;
	mlx_loop_hook(game->mlx, &game_play, game); //roda o jogo em loop
	mlx_key_hook(game->window, &ft_key, game); // verifica tecla foi pressionada
	mlx_hook(game->window, 33, 1L << 17, ft_close, game); // Clicar no X =ESC
	mlx_loop(game->mlx);
}
