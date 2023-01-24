/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:03:20 by wportilh          #+#    #+#             */
/*   Updated: 2023/01/23 20:38:14 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	will_collide(int angle, t_game *game)
{
	int		colision;
	float	pixel;

	colision = FALSE;
	pixel = -1;
	if (angle)
		ft_rotate(game, angle);
	while (++pixel < WIDTH)
	{
		calc_ray_dir(pixel, game);
		calc_delta_dist_x_and_y(game);
		calc_dist_to_side_x_and_y(game);
		calc_dda_find_wall(game);
		calc_perpendicular_distance(game);
		if ((game->dda.perpendicular_ray - (float)0.1) < (float)0.1)
			colision = TRUE;
	}
	if (angle)
		ft_rotate(game, angle * -1);
	return (colision);
}
