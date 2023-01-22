/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 09:00:06 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/22 13:22:56 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dist_order(t_game	*game)
{
	int	i;

	i = -1;
	while (++i < game->spr.count)
	{
		game->spr.order[i] = i;
		game->spr.dist[i] = ((game->player.pos[0] - game->spr_pos[i].x)
					* (game->player.pos[0] - game->spr_pos[i].x) + (game->player
						.pos[1] - game->spr_pos[i]. y) * (game->player.pos
					[1] - game->spr_pos[i].y));
		printf("spr_pos_i_x %f spr_pos_i_xy%f\n",  game->spr_pos[i].x,  game->spr_pos[i].y);
		printf("pl_pos0 %f  pl_pos1 %f\n", game->player.pos[0], game->player.pos[1]);
		printf("spr_dist %f\n", game->spr.dist[i]);
	}

}

void	dist_order_sort(t_game *game)
{
	int		i;
	int		j;
	float	tmp;

	dist_order(game);
	i = -1;
	while (++i < game->spr.count)
	{
		j = -1;
		while (++j < game->spr.count - 1)
		{
			if (game->spr.dist[j] < game->spr.dist[j + 1])
			{
				tmp = game->spr.dist[j];
				game->spr.dist[j] = game->spr.dist [j + 1];
				game->spr.dist[j + 1] = tmp;
				tmp = game->spr.order[j];
				game->spr.order[j] = game->spr.order[j + 1];
				game->spr.order[j + 1] = tmp;
			}
		}
	}
	printf("order0  %d dist0  %f\n",game->spr.order[0], game->spr.dist[0]);
	printf("order1  %d dist1  %f\n",game->spr.order[1], game->spr.dist[1]);
}

void	spr_raycast(t_game	*game, int i)
{
	game->spr.spr_x = game->spr_pos[game->spr.order[i]].x - game->player.pos[0];
	printf("spr_x =%f\n", game->spr.spr_x);
	game->spr.spr_y = game->spr_pos[game->spr.order[i]].y - game->player.pos[1];

	game->spr.invert = 1.0 / (game->player.camera_plane[0] * game->player.dir[1]
		- game->player.camera_plane[1] * game->player.dir[0]);

	game->spr.adjust_x = game->spr.invert * (game->player.dir[1] * game->spr
		.spr_x - game->player.dir[0] * game->spr.spr_y);

	game->spr.adjust_y = game->spr.invert * (- game->player.camera_plane[1]
			* game->spr.spr_x + game->player.camera_plane[0] * game->spr.spr_y);

	game->spr.screenx = (int)((WIDTH / 2) * (1 + game->spr.adjust_x / game->spr.adjust_y));

	game->spr.height = abs((int)(HEIGHT) / game->spr.adjust_y);
	game->spr.line_start_y = - game->spr.height / 2 + HEIGHT / 2;
	if ( game->spr.line_start_y < 0)
		game->spr.line_start_y = 0;

	game->spr.line_end_y = game->spr.height / 2 + HEIGHT / 2;
	if ( game->spr.line_end_y >= HEIGHT)
		game->spr.line_end_y = HEIGHT;

	game->spr.width = abs((int)(HEIGHT / (game->spr.adjust_y)));

	game->spr.line_start_x = -game->spr.width / 2 + game->spr.screenx;
	if (game->spr.line_start_x < 0)
		game->spr.line_start_x = 0;
	printf("spr.wdt%d, spr.scrx %d\n", game->spr.width, game->spr.screenx );

	game->spr.line_end_x = game->spr.width / 2 + game->spr.screenx;
	if (game->spr.line_end_x >= WIDTH)
		game->spr.line_end_x = WIDTH;
	printf("st%d, en %d\n", game->spr.line_start_x, game->spr.line_end_x );
}

void	draw_sprite(t_game *game, int y, int texx, int start)
{
	int	d;
	int	texy;

	while (y < game->spr.line_end_y)
	{
		d = (y) * 256 - HEIGHT * 128 + game->spr.height * 128;
		texy = ((d * game->textu[4].img.hgt) / game->spr.height) / 256;
		if (game->textu[4].img.data[texy * game->textu[4].img.size_l / 4 + texx] != -16777216)
		{
//			game->img.addr[y * game->img.size_l / 4 + start] = game->
//			textu[4].img.addr[texy * game->textu[4].img.size_l / 4 + texx];
//			game->img.data[y * game->img.size_l / 4 + start] = game->textu[4].img.data[texy * game->textu[4].img.size_l / 4 + texx];
//			game->img.data[y + start] = game->textu[4].img.data[game->textu[4].img.wdt * texy + texx];
			game->img.data[y * game->img.size_l / 4 + start] = WHITE;
			printf("%d\n", y * game->img.size_l / 4 + start);
		}
		y++;
	}
}

void	sprite_main(t_game	*game)
{
	int	i;
	int	y;
	int	start;
	int	texx;

	i = -1;
	dist_order_sort(game);
	while(++i < game->spr.count)
	{
		spr_raycast(game, i);
		start = game->spr.line_start_x;
		printf("start%d\n", start);
		printf("end%d\n", game->spr.line_end_x);
		printf("game->spr.order %d\n", game->spr.order[0]);
		while (start < game->spr.line_end_x)
		{
			texx = (int)(256 * (start - (- game->spr.width / 2 + game->spr
				.screenx)) * game->textu[4].img.wdt / game->spr.width) / 256;
			if (game->spr.adjust_y > 0 && start >= 0 && start < WIDTH && game->spr.adjust_y < game->spr.zbuffer[start])
			{
				y = game->spr.line_start_y;
	//			y = (int)(0.0 / game->spr.adjust_y);
				draw_sprite(game, y, texx, start);
			}
			start++;
		}
	}
}
