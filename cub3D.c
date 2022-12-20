/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:41:17 by acosta-a          #+#    #+#             */
/*   Updated: 2022/12/20 17:04:32 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
//função abaixo não esta pronta mas será pra checar se o argumento termina com .cub

int	check_args (char **argv)
{
	int		map_len;
	char	*map_name;

	map_len = ft_strlen (argv[1]);
	if (map_len > 5)
		map_name = ft_substr(argv[1], (map_len - 5), 5);
	if (ft_strncmp(map_name, ".cub", 5))
	{
		printf("testando");
		return (0);
	}
	else
		exit(1);
}

//main principal já checa quantos argumentos e se for != de 2 ele sai
int main (int argc, char **argv)
{
	if (argc != 2)
		print_exit("Error\nType 2 arguments");
	check_args(argv);
}
