/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wportilh <wportilh@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/03 01:29:58 by wportilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

# define WIDTH 320
# define HEIGHT 200

/*Adiciona pixel por pixel nas coordenadas que damos*/
static void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->wdt + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

/*Adiciona um fundo à tela (preenche a metade da tela)*/
static void	fill_background(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < (HEIGHT / 2))
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(&game->img, x, y, 0XBEBEFF);
	}
	--y;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(&game->img, x, y, 0X696969);
	}
}

/* Inicializa as configurações do player
*/
static void	init_player(t_game *game)
{
	game->player.pos[0] = 5; // posição x do player no mapa;
	game->player.pos[1] = 5; // posição y do player no mapa;
	game->player.dir[0] = 0; // posição x do vetor dir no mapa (não muda);
	game->player.dir[1] = -1; // posição y do vetor dir no mapa (não muda);
	game->player.plane[0] = 0.66; // posição x do vetor plane no mapa (não muda);
	game->player.plane[1] = 0; // posição y do vetor plane no mapa (não muda);
}

/*	Cálculo dos raios.
	Quando calculo camera_pixel, não aloco o y com malloc, porque o valor dele não muda.
	game->player.plane[1] é o y, que sempre é 0. (se precisar no futuro, talvez na rotação, aloco ele também).
	Ou seja, o que interessa é calcular x, que varia.
	
	A mesma coisa se aplica ao ray_dir, mas acho que na rotação vou precisar (ou não kkk) alocar ele.
*/
static void	calc_ray_dir(t_game *game)
{
	float	i;
	float	vetor_size;
	float	*camera_pixel_x;
	float	*ray_dir_x;
	float	camera_pixel_y;
	float	ray_dir_y;

	camera_pixel_x = malloc((WIDTH + 1) * sizeof(float));
	if (!camera_pixel_x)
		exit (EXIT_FAILURE);
	ray_dir_x = malloc((WIDTH + 1) * sizeof(float));
	if (!ray_dir_x)
		exit (EXIT_FAILURE);
	i = -1;
	while (++i <= WIDTH)
	{
		vetor_size = 2 * (i/WIDTH) - 1; // Calcula o tamanho do vetor dos raios em relação à player.plane
		camera_pixel_x[(int)i] = (vetor_size * game->player.plane[0]); // (multiplicação de vetores) Calcula a posição dos vetores dos raios
		ray_dir_x[(int)i] = camera_pixel_x[(int)i] + game->player.dir[0]; // (soma de vetores) Calcula a direção dos raios
	}
	camera_pixel_y = (vetor_size * game->player.plane[1]);
	ray_dir_y = -1;
	//i = -1;
	//while (++i <= WIDTH)
	//	printf("%f\n", camera_pixel_x[(int)i]);
	//printf("%f\n", i - 1);
}

void	play_game(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.wdt, &game->img.endian);
	fill_background(game);
	init_player(game);
	calc_ray_dir(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img.img_ptr, 0, 0);
	mlx_loop(game->mlx);
}
