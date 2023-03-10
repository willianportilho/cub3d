/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:28:40 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/23 21:30:16 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* remove all .cub spaces*/
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
