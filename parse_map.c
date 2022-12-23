/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:39:20 by wportilh          #+#    #+#             */
/*   Updated: 2022/12/23 18:54:56 by wportilh         ###   ########.fr       */
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

/*Pega somente o mapa, sem os elementos. Essa variável start é incrementada até achar as 6 correspondências com strnstr
  Se não acha, retorna erro. Com start, consigo saber de qual index eu começo a copiar o mapa*/
void    get_only_map(t_game *game)
{
    int i;
    int size;
    int start;

    i = -1;
    start = 0;
    while (start < 6 && game->map[++i])
    {
        size = ft_strlen(game->map[i]) - 1;
        if ((ft_strnstr(game->map[i], "WE", size) != 0)
        || (ft_strnstr(game->map[i], "EA", size) != 0)
        || (ft_strnstr(game->map[i], "NO", size) != 0)
        || (ft_strnstr(game->map[i], "SO", size) != 0)
        || (ft_strnstr(game->map[i], "F", size) != 0)
        || (ft_strnstr(game->map[i], "C", size) != 0))
            start++;
    }
    if (start < 6)
        map_error("needed 6 elements", game);
    game->map = ft_str_arrayndup_free(start, game->map); // Aqui eu coloco manualmente a posição do mapa. Depois podemos mudar isso.
    if (!game->map)
        return (destroy_pointers_char(game->map)); // Estou limpando aqui por enquanto, mas depois podemos unir na função clean se eu incluir game->map no t_game
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
    char **arr;

    i = -1;
    arr = game->map;
    while (arr[++i])
    {
        j = -1;
        while (arr[i][++j])
        {
            if (arr[i][j] == ' ')
            {
                if ((j > 0) && (ft_strchr("0ENSW", arr[i][j - 1])))
                    map_error("invalid format: needed 1 around the map", game); // Acho que vou fazer um define com essas mensagens depois
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

/*Essa fução checa se as linhas e colunas no index 0 e último index antes do '\0' são diferentes de espaço ' ' ou um '1'*/
void    check_walls_2(t_game *game)
{
    int i;
    int j;
    int size;

    i = -1;
    j = -1;
    size = ft_strlen(game->map[0]);
    while (game->map[++i]) // checa linhas
    {
        if ((ft_strchr("0ENSW", game->map[i][0])) // index 0
         || (ft_strchr("0ENSW", game->map[i][size - 1]))) // último index
            map_error("invalid format: needed '1' around the map", game);
    }
    while (++j < size) // checa colunas
    {
        if ((ft_strchr("0ENSW", game->map[0][j])) // index 0
         || (ft_strchr("0ENSW", game->map[ft_str_arraylen(game->map) - 1][j]))) // último index
            map_error("invalid format: needed '1' around the map", game);
    }
}

/*análise do mapa
  Essa análise pode ter várias funções no começo, mas aos poucos vou tentar diminuir e otimizar*/
void    parse_map(t_game *game)
{
    get_only_map(game);
    check_invalid_characters(game);
    check_walls_1(game);
    check_walls_2(game);
}
