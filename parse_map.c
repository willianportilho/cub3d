/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:39:20 by wportilh          #+#    #+#             */
/*   Updated: 2022/12/23 00:58:19 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Deixei tudo nesse arquivo para facilitar, mas depois que estiver ok, 
   eu mudo o que precisar de lugar para ficar mais clean*/

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

/* Retorna um novo array (vetor) alocado com malloc (a memória do array antigo não é liberada)
   Pelo menos por enquanto, estou pegando o game.map e fazendo o novo array a partir do mapa, depois dos elementos*/
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

/* Por enquanto, nessa função, itero o mapa e checo caracteres inválidos. Aceito somente esses: " 01ENSW"*/
void    check_invalid_characters(char ***map)
{
    int i;
    int j;

    i = -1;
    j = -1;
    while((*map)[++i])
    {
        while((*map)[i][j])
        {
            if (ft_strchr(" 10ENSW", (*map)[i][++j]) == NULL)
            {
                // estou colocando bastante informações por enquanto para facilitar no desenvolvimento
                printf("Error\ninvalid character: '%d' (line %d, column %d)\n", (*map)[i][j], i + 1, j + 1);
                destroy_pointers_char(*map);
                exit(-1);
            }
        }
        j = -1;
    }
}

/* Checa se as linhas do mapa começam com 1 da esquerda para a direita.*/
void    check_walls_line_left(char ***map)
{
    int i;
    int j;
    int check_wall;

    i = -1;
    j = -1;
    check_wall = FALSE;
    while ((*map)[++i])
    {
        while ((*map)[i][++j])
        {
            if ((*map)[i][j] == '1')
            {
                check_wall = TRUE;
                break ;
            }
            else if ((*map)[i][j] != ' ')
            {
                printf("Error\ninvalid format: '%c' (line %d, column %d): 1 are required around the map\n", (*map)[i][j], i + 1, j + 1);
                destroy_pointers_char(*map);
                exit (-1);
            }
        }
        if (check_wall == FALSE)
        {
            printf("Error\ninvalid format: '%c' (line %d, column %d): 1 are required around the map\n", (*map)[i][j], i + 1, j + 1);
            destroy_pointers_char(*map);
            exit (-1);
        }
        j = -1;
        check_wall = FALSE;
    }
}

/*análise do mapa
  Essa análise pode ter várias funções no começo, mas aos poucos vou tentar diminuir e otimizar*/
void    parse_map(t_game *game)
{
    char    **only_map;

    only_map = ft_str_arraydup(game->map + 6); // Aqui eu coloco manualmente a posição do mapa. Depois podemos mudar isso.
    if (!only_map)
        return (destroy_pointers_char(only_map)); // Estou limpando aqui por enquanto, mas depois podemos unir na função clean se eu incluir only_map no t_game
    //print_vector(only_map); // Aqui eu imprimo o novo mapa para testes
    //print_vector(game->map); //Aqui eu imprimo todo o .cub
    check_invalid_characters(&only_map);
    check_walls_line_left(&only_map);
    destroy_pointers_char(only_map);
}
