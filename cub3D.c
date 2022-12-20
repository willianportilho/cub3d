/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:41:17 by acosta-a          #+#    #+#             */
/*   Updated: 2022/12/20 19:51:53 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
//checagem de argumentos finalizada, estou checando se o arquivo mapa é .cub, caso não seja programa é finalizado

void	check_args (char **argv)
{
	int		map_len;
	char	*map_name;

	map_len = ft_strlen (argv[1]);
	if (map_len > 4)
		map_name = ft_substr(argv[1], (map_len - 4), 5);
	else
		print_exit("Map must be .cub\n");
	printf("%d \n", map_len);
	if (!ft_strncmp(map_name, ".cub", 5))
	{
		printf("%s \n", map_name);
		free(map_name);
		return ;
	}
	free(map_name);
	print_exit("Map must be .cub\n");
}

//main principal já checa quantos argumentos e se for != de 2 ele sai
int main (int argc, char **argv)
{
	if (argc != 2)
		print_exit("Error\nType 2 arguments");
	check_args(argv);
	// vou iniciar agora o parser dos argumentos iniciais antes do mapa
//	parser_map_args();
}
