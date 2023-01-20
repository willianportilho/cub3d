/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:28:40 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/19 23:30:55 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_close(t_game *game)
{
	int	i;

	i = -1;
	printf("Bye bye\n");
	while (++i < 4)
		if (game->textu[i].img.img_ptr)
			mlx_destroy_image(game->mlx, game->textu[i].img.img_ptr);
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	clean_exit(game);
	return (1);
}

void	texture_error(char *message, t_game *game)
{
	int	i;

	i = -1;
	printf("Bye bye\n");
	while (++i < 4)
		if (game->textu[i].img.img_ptr)
			mlx_destroy_image(game->mlx, game->textu[i].img.img_ptr);
	printf("%s\n", message);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	clean_exit(game);
}
