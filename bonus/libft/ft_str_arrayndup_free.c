/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arrayndup_free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:32:28 by wportilh          #+#    #+#             */
/*   Updated: 2022/12/26 15:37:15 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str_arrayndup_free(size_t start, char **array)
{
	size_t	i;
	char	**new_array;

	if (!array)
		return (NULL);
	if (start >= ft_str_arraylen(array))
		return (NULL);
	new_array = malloc((ft_str_arraylen(array) - start + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = -1;
	while (array[start])
	{
		new_array[++i] = ft_strdup(array[start++]);
		if (!new_array[i])
			return (NULL);
	}
	new_array[++i] = NULL;
	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
	return (new_array);
}
