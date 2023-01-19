/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/19 00:40:46 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_rotate(t_game *game, double angle)
{
	float	tmp;
	float	tmpplane;

	tmp = cos(angle) * game->player.dir[0] - sin(angle) * game->player.dir[1];
	game->player.dir[1] = sin(angle) * game->player.dir[0] + cos(angle)
		* game->player.dir[1];
	game->player.dir[0] = tmp;
	tmpplane = cos(angle) * game->player.camera_plane[0] - sin(angle)
		* game->player.camera_plane[1];
	game->player.camera_plane[1] = sin(angle) * game->player.camera_plane[0]
		+ cos(angle)
		* game->player.camera_plane[1];
	game->player.camera_plane[0] = tmpplane;
}

void	up_down(t_game *game, int direction)
{
	float	speed;
	float	pos;
	float	check_pos_x;
	float	check_pos_y;

	speed = 0.1;
	if (direction == UP)
	{
/*		pos = game->player.pos[0] + game->player.dir[0] * speed;
		if (game->map[(int)pos][(int)game->player.pos[1]] == '0')
			game->player.pos[0] += game->player.dir[0] * speed;
		pos = game->player.pos[1] + game->player.dir[1] * speed;
		if (game->map[(int)game->player.pos[0]][(int)pos] == '0')
			game->player.pos[1] += game->player.dir[1] * speed;

*/
		check_pos_x = (game->player.pos[0] + game->player.dir[0] * speed) - 0.1;
		check_pos_y = (game->player.pos[1] + game->player.dir[1] * speed) - 0.1;
		printf("x = %f\n", check_pos_x);
		printf("y = %f\n", check_pos_y);
		if (game->map[(int)check_pos_y][(int)check_pos_x] != '1')
		{
			game->player.pos[0] += game->player.dir[0] * speed;
			game->player.pos[1] += game->player.dir[1] * speed;
		}
	}
	if (direction == DOWN)
	{
		pos = game->player.pos[0] + game->player.dir[0] * speed;
		if (game->map[(int)pos][(int)game->player.pos[1]] == '0')
			game->player.pos[0] -= game->player.dir[0] * speed;
		pos = game->player.pos[1] + game->player.dir[1] * speed;
		if (game->map[(int)game->player.pos[0]][(int)pos] == '0')
			game->player.pos[1] -= game->player.dir[1] * speed;

	}
}

void	left_right(t_game *game, int direction)
{
	float	speed;
	float	pos;

	speed = 0.1;
	if (direction == LEFT)
	{
		pos = game->player.pos[0] + game->player.dir[1] * speed;
		if (game->map[(int)pos]
			[(int)game->player.pos[1]] == '0')
			game->player.pos[0] += game->player.dir[1] * speed;
		pos = game->player.pos[1] - game->player.dir[0] * speed;
		if (game->map[(int)game->player.pos[0]][(int)pos] == '0')
			game->player.pos[1] -= game->player.dir[0] * speed;
	}
	if (direction == RIGHT)
	{
		pos = game->player.pos[0] - game->player.dir[1] * speed;
		if (game->map[(int)pos]
			[(int)game->player.pos[1]] == '0')
			game->player.pos[0] -= game->player.dir[1] * speed;
		pos = game->player.pos[1] + game->player.dir[0] * speed;
		if (game->map[(int)game->player.pos[0]][(int)pos] == '0')
			game->player.pos[1] += game->player.dir[0] * speed;
	}
}

int	ft_key(int key, t_game *game)
{
	if (key == 113 || key == 65307)
		ft_close(game);
	else if (key == W)
		up_down(game, UP);
	else if (key == S)
		up_down(game, DOWN);
	else if (key == A)
		left_right(game, LEFT);
	else if (key == D)
		left_right(game, RIGHT);
	else if (key == 65361)
		ft_rotate(game, -PI / 100);
	else if (key == 65363)
		ft_rotate(game, +PI / 100);
	load_game(game);
}
