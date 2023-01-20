/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:06:16 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/19 23:49:14 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calc_ray_dir(float pixel, t_game *game)
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
		game->delta.dist_y = -1;
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
		game->delta.dist_x = -1;
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
	game->dist.side_x = (game->player.pos[0]
			- (float)game->dda.map_pos[0]) * game->delta.dist_x;
	game->dda.step_x = -1;
	if (game->ray.dir_x > 0)
	{
		game->dist.side_x = ((float)game->dda.map_pos[0]
				+ 1.0 - game->player.pos[0]) * game->delta.dist_x;
		game->dda.step_x = 1;
	}
	game->dist.side_y = (game->player.pos[1]
			- (float)game->dda.map_pos[1]) * game->delta.dist_y;
	game->dda.step_y = -1;
	if (game->ray.dir_y > 0)
	{
		game->dist.side_y = ((float)game->dda.map_pos[1]
				+ 1.0 - game->player.pos[1]) * game->delta.dist_y;
		game->dda.step_y = 1;
	}
}

void	calc_dda_find_wall(t_game *game)
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
		if (game->map[(int)game->dda.wall_map_pos_y]
			[(int)game->dda.wall_map_pos_x] == '1')
			hit = TRUE;
	}
}

void	calc_perpendicular_distance(t_game *game)
{
	if (game->dda.hit_side == 0)
	{
		game->dda.perpendicular_ray = (game->dda.wall_map_pos_x
				- game->player.pos[0] + ((1 - game->dda.step_x) / 2));
		game->dda.perpendicular_ray /= game->ray.dir_x;
	}
	else
	{
		game->dda.perpendicular_ray = (game->dda.wall_map_pos_y
				- game->player.pos[1] + ((1 - game->dda.step_y) / 2));
		game->dda.perpendicular_ray /= game->ray.dir_y;
	}
}
