/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arraylen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:25:16 by wportilh          #+#    #+#             */
/*   Updated: 2022/12/26 15:26:11 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_str_arraylen(char **array)
{
	size_t	array_size;

	if (!array)
		return (-1);
	array_size = 0;
	while (array[array_size])
		array_size++;
	return (array_size);
}
