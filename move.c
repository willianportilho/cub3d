/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/20 19:53:44 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*	rotates the player*/
void	ft_rotate(t_game *game, double angle)
{
	float	tmp;
	float	tmpplane;

	tmp = cos(angle) * game->player.dir[0] - sin(angle) * game->player.dir[1];
	game->player.dir[1] = sin(angle) * game->player.dir[0] + cos(angle)
		* game->player.dir[1];
	game->player.dir[0] = tmp;
	tmpplane = cos(angle) * game->player.camera_plane[0]
		- sin(angle) * game->player.camera_plane[1];
	game->player.camera_plane[1] = sin(angle) * game->player.camera_plane[0]
		+ cos(angle) * game->player.camera_plane[1];
	game->player.camera_plane[0] = tmpplane;
}

/*
	UP and DOWN
	up_down e left_right funcionam da mesma maneira, elas somam a posição do
	player no eixo 0 =x e eixo 1 = y quanto o player andou baseado na direção
	que ele está apontando. Se trata de uma soma de vetores.
*/
void	up_down(t_game *game, int direction)
{
	float	speed;

	speed = 0.1;
	if (direction == UP)
	{
		if (will_collide(FALSE, game) != TRUE)
		{
			game->player.pos[0] += game->player.dir[0] * speed;
			game->player.pos[1] += game->player.dir[1] * speed;
		}
	}
	if (direction == DOWN)
	{
		if (will_collide(PI, game) != TRUE)
		{
			game->player.pos[0] -= game->player.dir[0] * speed;
			game->player.pos[1] -= game->player.dir[1] * speed;
		}
	}
}

/* moves LEFT/RIGHT*/
void	left_right(t_game *game, int direction)
{
	float	speed;

	speed = 0.1;
	if (direction == LEFT)
	{
		if (will_collide(-PI / 2, game) != TRUE)
		{
			game->player.pos[0] += game->player.dir[1] * speed;
			game->player.pos[1] -= game->player.dir[0] * speed;
		}
	}
	if (direction == RIGHT)
	{
		if (will_collide(PI / 2, game) != TRUE)
		{
			game->player.pos[0] -= game->player.dir[1] * speed;
			game->player.pos[1] += game->player.dir[0] * speed;
		}
	}
}

/* detect keys WSAD and arrow left/right*/
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
