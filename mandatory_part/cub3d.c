/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:41:17 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/25 22:17:03 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**read_cubfile(char *map, t_game *game)
{
	int		fd;
	char	*line;
	char	**vector_map;

	fd = open(map, O_DIRECTORY);
	if (fd != -1)
		print_exit("file cannot be a directory");
	fd = open(map, O_RDONLY);
	if (fd == -1)
		print_exit("file cannot be a opened");
	game->single_line_map = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		game->single_line_map = ft_strjoin(game->single_line_map, line);
		free(line);
		line = get_next_line(fd);
	}
	vector_map = ft_split(game->single_line_map, '\n');
	return (vector_map);
}

static void	check_args(char **argv)
{
	int		map_len;
	char	*map_name;

	map_len = ft_strlen (argv[1]);
	if (map_len > 4)
		map_name = ft_substr(argv[1], (map_len - 4), 5);
	else
		print_exit("map must be .cub\n");
	if (!ft_strncmp(map_name, ".cub", 5))
	{
		free(map_name);
		return ;
	}
	free(map_name);
	print_exit("map must be .cub\n");
}

static void	init_game(t_game *game)
{
	int	i;

	i = -1;
	game->settings_count = 0;
	game->i = 0;
	game->no_wall_path = NULL;
	game->so_wall_path = NULL;
	game->we_wall_path = NULL;
	game->ea_wall_path = NULL;
	game->c_inputs = NULL;
	game->f_inputs = NULL;
	while (++i < 4)
		game->textu[i].img.img_ptr = NULL;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		print_exit("required 2 arguments");
	init_game(&game);
	check_args(argv);
	game.map = read_cubfile(argv[1], &game);
	parse_settings(&game, game.map);
	parse_map(&game);
	play_game(&game);
	clean_exit(&game);
}
