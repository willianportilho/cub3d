/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:41:17 by acosta-a          #+#    #+#             */
/*   Updated: 2022/12/21 00:41:53 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*função que faz leitura do mapa e o transforma em um vetor
ela retorna um vetor onde cada indice do vetor é uma linha*/
char	**read_cubfile(char *map)
{
	int		fd;
	char	*line;
	char	**vector_map;
	char	*single_line_map;

	fd = open(map, O_DIRECTORY);
	if (fd != -1)
		print_exit("File cannot be a directory");
	fd = open(map, O_RDONLY);
	single_line_map = '\0';
	line = get_next_line(fd);
	while (line != NULL)
	{
		single_line_map = ft_strjoin(single_line_map, line);
		free(line);
		line = get_next_line(fd);
	}
	vector_map = ft_split(single_line_map, '\n');
	free(single_line_map);
	return (vector_map);
}

/*check_args OK: função checando se o arquivo mapa é .cub
	, caso não seja programa é finalizado*/
void	check_args(char **argv)
{
	int		map_len;
	char	*map_name;

	map_len = ft_strlen (argv[1]);
	if (map_len > 4)
		map_name = ft_substr(argv[1], (map_len - 4), 5);
	else
		print_exit("Map must be .cub\n");
	if (!ft_strncmp(map_name, ".cub", 5))
	{
		free(map_name);
		return ;
	}
	free(map_name);
	print_exit("Map must be .cub\n");
}

void	init_game(t_game *game)
{
	//não precisei alocar memoria abaixo mass acho que vai precisar
//	game = malloc(sizeof(t_game));
//	game = ft_calloc(sizeof(t_game), 1);
	game->x = 99;
}

/*main principal já checa quantos argumentos e se for != de 2 ele sai*/
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		print_exit("Error\nType 2 arguments");
	init_game(&game);
	check_args(argv);
	game.map = read_cubfile(argv[1]); // lendo o mapa e transformando em vetor
//	parse_setting();
	clean_exit(&game);
}
