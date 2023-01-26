/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_mlx_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:28:40 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/25 20:04:27 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_close(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 6)
		if (game->textu[i].img.img_ptr)
			mlx_destroy_image(game->mlx, game->textu[i].img.img_ptr);
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx, game->img.img_ptr);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	clean_exit(game);
	return (EXIT_FAILURE);
}

void	texture_error(char *message, t_game *game)
{
	int	i;

	i = -1;
	while (++i < 6)
		if (game->textu[i].img.img_ptr)
			mlx_destroy_image(game->mlx, game->textu[i].img.img_ptr);
	printf("Error\n%s\n", message);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	clean_exit(game);
}

void	print_exit(char *input)
{
	printf("Error\n%s\n", input);
	exit (EXIT_FAILURE);
}
