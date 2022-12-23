/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:39:20 by wportilh          #+#    #+#             */
/*   Updated: 2022/12/23 16:19:51 by wportilh         ###   ########.fr       */
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

/* Retorna um novo array (vetor) alocado com malloc (a memória do array É LIBERADA, antes não era)
   start define de qual index a cópia comecará
   Pelo menos por enquanto, estou pegando o game.map e fazendo o novo array a partir do mapa, depois dos elementos*/
char    **ft_str_arrayndup_free(size_t start, char **array)
{
    size_t  i;
    char    **new_array;

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
    destroy_pointers_char(array);
    return (new_array);
}

int map_error(char *message, t_game *game)
{
    // estou colocando bastante informações por enquanto para facilitar no desenvolvimento
    printf("Error\n%s\n", message);
    clean_exit(game);
    exit(-1);
}

/* Por enquanto, nessa função, itero o mapa e checo caracteres inválidos. Aceito somente esses: " 01ENSW"*/
void    check_invalid_characters(t_game *game)
{
    int i;
    int j;

    i = -1;
    while(game->map[++i])
    {
        j = -1;
        while(game->map[i][++j])
        {
            if (ft_strchr(" 10ENSW", game->map[i][j]) == NULL)
                map_error("invalid character", game);
        }
    }
}

/* Aqui estou testando uma outra abordagem que parece melhor, para checar se ' ' espaços estão ao lado de um caratere proibido "0ENSW"
   os espaços só podem ficar ao lado de espaços ' ' e muros '1'
   Por enquanto, eu tirei o "!= NULL" das checagens para caber na norma (80 colunas), mas depois vejo se consigo otimizar para ficar mais legível*/
void    check_walls_1(t_game *game)
{
    int i;
    int j;
    int size;
    char **arr;

    i = -1;
    arr = game->map;
    size = ft_strlen(arr[0]);
    while (arr[++i])
    {
        j = -1;
        if ((ft_strchr("0ENSW", arr[i][0])) || (ft_strchr("0ENSW", arr[i][size - 1])))
            map_error("invalid format: needed '1' around the map", game);
        while (arr[i][++j])
        {
            if (arr[i][j] == ' ')
            {
                if ((j > 0) && (ft_strchr("0ENSW", arr[i][j - 1])))
                    map_error("invalid format: needed 1 around the map", game);
                if ((arr[i][j + 1]) && (ft_strchr("0ENSW", arr[i][j + 1])))
                    map_error("invalid format: needed 1 around the map", game);
                if ((i > 0) && (ft_strchr("0ENSW", arr[i - 1][j])))
                    map_error("invalid format: needed 1 around the map", game);
                if ((arr[i + 1]) && (ft_strchr("0ENSW", arr[i + 1][j])))
                    map_error("invalid format: needed 1 around the map", game);
            }
        }
    }
}

/*análise do mapa
  Essa análise pode ter várias funções no começo, mas aos poucos vou tentar diminuir e otimizar*/
void    parse_map(t_game *game)
{
    game->map = ft_str_arrayndup_free(6, game->map); // Aqui eu coloco manualmente a posição do mapa. Depois podemos mudar isso.
    if (!game->map)
        return (destroy_pointers_char(game->map)); // Estou limpando aqui por enquanto, mas depois podemos unir na função clean se eu incluir game->map no t_game
    check_invalid_characters(game);
    check_walls_1(game);
}
