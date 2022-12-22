/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:39:20 by wportilh          #+#    #+#             */
/*   Updated: 2022/12/22 18:16:36 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Retorna o tamanho de um array (vetor) de string*/
size_t  ft_str_arraylen(char **array)
{
    size_t  array_size;

    if (!array)
        return(-1);
    array_size = 0;
    while (array[array_size])
        array_size++;
    return (array_size);
}

/* Retorna um novo array (vetor) alocado com malloc (a memória do array antigo não é liberada)*/
/* Pelo menos por enquanto, estou pegando o game.map e fazendo o novo array a partir do mapa, depois dos elementos*/
char    **ft_str_arraydup(char **array)
{
    int     i;
    char    **new_array;

    if (!array)
        return (NULL);
    i = -1;
    new_array = malloc((ft_str_arraylen(array) + 1) * sizeof(char *));
    if (!new_array)
        return (NULL);
    while (array[++i])
    {
        new_array[i] = ft_strdup(array[i]);
        if (!new_array[i])
            return (NULL);
    }
    new_array[i] = NULL;
    return (new_array);
}

/*análise do mapa*/
void    parse_map(t_game *game)
{
    char    **only_map;

    only_map = ft_str_arraydup(game->map + 6); // Aqui eu coloco manualmente a posição do mapa. Depois podemos mudar isso.
    print_vector(only_map); //Aqui eu imprimo o novo mapa para testes
    //print_vector(game->map); //Aqui eu imprimo todo o .cub
}
