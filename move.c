/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/07 00:32:01 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_rotate(t_game *game, double angle) // rotaciona o player
{
	float    tmp;
    float    tmpplane;

    tmp = cos(angle) * game->player.dir[0]  - sin(angle) * game->player.dir[1];
    game->player.dir[1] = sin(angle) * game->player.dir[0]  + cos(angle)
        * game->player.dir[1];
    game->player.dir[0] = tmp;

    tmpplane = cos(angle) * game->player.camera_plane[0] - sin(angle) * game->player.camera_plane[1];
    game->player.camera_plane[1]  = sin(angle) * game->player.camera_plane[0] + cos(angle)
        * game->player.camera_plane[1] ;
    game->player.camera_plane[0] = tmpplane;
}
// up_down e left_right funcionam da mesma maneira, elas somam a posição do player no eixo 0 =x e eixo 1 = y quanto o player andou baseado na direção que ele está apontando. Se trata de uma soma de vetores.
void	up_down(t_game *game, int direction) // função pra cima e baixo
{
	int	speed;

	speed = 1;
	if (direction == UP)
	{
		if(game->map[(int)(game->player.pos[0] + game->player.dir[0] * speed)]
			[(int)game->player.pos[1]] == '0');
			game->player.pos[0] += game->player.dir[0] * speed;
		if(game->map[(int)game->player.pos[0]][(int)(game->player.pos[1] +
			game->player.dir[1] * speed)] == '0');
			game->player.pos[1] += game->player.dir[1] * speed;
	}
	if (direction == DOWN)
	{
		if(game->map[(int)(game->player.pos[0] + game->player.dir[0] * speed)]
			[(int)game->player.pos[1]] == '0');
			game->player.pos[0] -= game->player.dir[0] * speed;
		if(game->map[(int)game->player.pos[0]][(int)(game->player.pos[1] +
			game->player.dir[1] * speed)] == '0');
			game->player.pos[1] -= game->player.dir[1] * speed;
	}
}

void	left_right(t_game *game, int direction) // função pra mover esq/dir
{
	int	speed;

	speed = 1;
	if (direction == RIGHT)
	{
		if(game->map[(int)(game->player.pos[0] + game->player.dir[1] * speed)]
			[(int)game->player.pos[1]] == '0');
			game->player.pos[0] += game->player.dir[1] * speed;
		if(game->map[(int)game->player.pos[0]][(int)(game->player.pos[1] -
			game->player.dir[0] * speed)] == '0');
			game->player.pos[1] -= game->player.dir[0] * speed;
	}
	if (direction == LEFT)
	{
		if(game->map[(int)(game->player.pos[0] - game->player.dir[1] * speed)]
			[(int)game->player.pos[1]] == '0');
			game->player.pos[0] -= game->player.dir[1] * speed;
		if(game->map[(int)game->player.pos[0]][(int)(game->player.pos[1] +
			game->player.dir[0] * speed)] == '0');
			game->player.pos[1] += game->player.dir[0] * speed;
	}
}

int		ft_key(int key, t_game *game) // leitura de teclas
{
	if (key == 113 || key == 65307)
		ft_close(game);
	else if (key == W)
		up_down(game , UP);
	else if (key == S)
		up_down(game , DOWN);
	else if (key == A)
		left_right(game , LEFT);
	else if (key == D)
		left_right(game , RIGHT);
	else if (key == 65361) // gira pra esquerda pressionando seta
		ft_rotate(game, PI / 36);
	else if (key == 65363)// gira pra direita pressionando seta
		ft_rotate(game, -PI / 36);
	game_play(game);
}
