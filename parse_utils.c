/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:28:40 by acosta-a          #+#    #+#             */
/*   Updated: 2022/12/26 15:23:30 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*função remove todos espaços do arquivo .cub*/

char	*remove_space(char *str)
{
	int	char_count;
	int	i;

	char_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			str[char_count] = str[i];
			char_count++;
		}
		i++;
	}
	str[char_count] = '\0';
	return (str);
}

/* printa error seguido da mensagem da nossa escolha
e chama a função clean para não dar leak*/
int	map_error(char *message, t_game *game)
{
	printf("Error\n%s\n", message);
	clean_exit(game);
	exit(-1);
}