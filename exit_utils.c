/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:28:40 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/19 00:34:25 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_exit(char *input)
{
	printf("%s", input);
	exit (1);
}

void	clean_exit(t_game *game)
{
	destroy_pointers_char(game->map);
	free(game->single_line_map);
	free(game->no_wall_path);
	free(game->so_wall_path);
	free(game->we_wall_path);
	free(game->ea_wall_path);
	free(game->c_inputs);
	free(game->f_inputs);
	exit (1);
}

void	destroy_pointers_char(char **p)
{
	int	i;

	i = 0;
	while (p != NULL && p[i] != NULL)
		free(p[i++]);
	free(p);
}

int	map_error(char *message, t_game *game)
{
	printf("Error\n%s\n", message);
	clean_exit(game);
	exit(-1);
}

void	map_missing_error(char *message, t_game *game)
{
	printf("Error\n%s\n", message);
	destroy_pointers_char(game->map);
	free(game->single_line_map);
	if (game->no_wall_path)
		free(game->no_wall_path);
	if (game->so_wall_path)
		free(game->so_wall_path);
	if (game->we_wall_path)
		free(game->we_wall_path);
	if (game->ea_wall_path)
		free(game->ea_wall_path);
	if (game->c_inputs)
		free(game->c_inputs);
	if (game->f_inputs)
		free(game->f_inputs);
	exit (1);
}

void	print_vector(char **p) ///deletar essa função!
{
	int	i;

	i = 0;
	while (p != NULL && p[i] != NULL)
		printf("%s\n", p[i++]);
}
