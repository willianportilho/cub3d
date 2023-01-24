/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:28:40 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/23 22:49:46 by acosta-a         ###   ########.fr       */
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
	if (game->s1_path)
		free(game->s1_path);//bonus
	if (game->s2_path)
		free(game->s2_path);//bonus
	free(game->spr_pos); //bonus
	free(game->spr.order);//bonus
	free(game->spr.dist);//bonus
	free(game->spr.zbuffer);//bonus
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
	if (game->s1_path)
		free(game->s1_path);//bonus
	if (game->s2_path)
		free(game->s2_path);//bonus
	exit (1);
}
