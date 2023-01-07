/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:03:00 by acosta-a          #+#    #+#             */
/*   Updated: 2023/01/06 21:59:23 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	game->player.pos[0] = 3; // posição x do player no mapa;
	game->player.pos[1] = 3; // posição y do player no mapa;
	game->player.dir[0] = 1.0; // posição x do vetor dir no mapa (não muda);
	game->player.dir[1] = 1.0; // posição y do vetor dir no mapa (não muda);
	game->player.plane[0] = 0.66; // posição x do vetor plane no mapa (não muda);
	game->player.plane[1] = 0; // posição y do vetor plane no mapa (não muda);
	//game->player.dir[0] = (game->player.dir[0] * cos(45)) - (game->player.dir[1] * sin(45));
    //game->player.plane[1] = (game->player.plane[0] * sin(45)) + (game->player.plane[1] * cos(45));
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
	float	camera_pixel_x;
	float	camera_pixel_y;

	game->ray.ray_dir_x = malloc((WIDTH + 1) * sizeof(float));
	if (!game->ray.ray_dir_x)
		exit (EXIT_FAILURE);
	i = -1;
	while (++i <= WIDTH)
	{
		vetor_size = 2 * (i/WIDTH) - 1; // Calcula o tamanho do vetor dos raios em relação à player.plane
		camera_pixel_x = (vetor_size * game->player.plane[0]); // (multiplicação de vetores) Calcula a posição dos vetores x dos raios
		game->ray.ray_dir_x[(int)i] = camera_pixel_x + game->player.dir[0]; // (soma de vetores) Calcula a direção x dos raios
	}
	camera_pixel_y = vetor_size * game->player.plane[1]; // (multiplicação de vetores) Calcula a posição dos vetores y dos raios
	game->ray.ray_dir_y = camera_pixel_y + game->player.dir[1]; // (soma de vetores) Calcula a direção y dos raios.
}

/*	Cálculo dos deltas, que são as distâncias x e y usadas no algoritmo DDA para detectar os muros.
	No caso do x, obteremos a distância para x chegar a alguma linha vertical.
	No caso do y, obteremos a distância para y chegar a alguma linha horizontal.
*/
void	calc_delta_dist_x_and_y(t_game *game)
{
	int		i;
	//float	ray_dir_hypotenuse; // não é mais necessário

	game->delta.delta_dist_x = malloc((WIDTH + 1) * sizeof(float));
	if (!game->delta.delta_dist_x)
		exit (EXIT_FAILURE);
	game->delta.delta_dist_y = malloc((WIDTH + 1) * sizeof(float));
	if (!game->delta.delta_dist_y)
		exit (EXIT_FAILURE);
	i = -1;
	while (++i <= WIDTH)
	{
		//ray_dir_hypotenuse = sqrt(pow(game->ray.ray_dir_x[i], 2) + pow(game->ray.ray_dir_y, 2)); // Magnitude do ray dir *Não é mais necessário
		if (game->ray.ray_dir_x[i] == 0) // Tratamento caso 0
		{
			game->ray.ray_dir_x[i] = 1;
			game->ray.ray_dir_y = 0;
		}
		else
		{
			if (game->ray.ray_dir_y > 0)
				game->delta.delta_dist_x[i] = 1 / game->ray.ray_dir_x[i]; // magnitude do ray_dir dividida por ray dir_x (semelhança de triângulos) *agora é dividido por 1 para simplificar
		}
		if (game->ray.ray_dir_y == 0) // Tratamento caso 0
		{
			game->ray.ray_dir_y = 1;
			game->ray.ray_dir_x[i] = 0;
		}
		else
		{
			if (game->ray.ray_dir_x[i] > 0)
				game->delta.delta_dist_y[i] = 1 / game->ray.ray_dir_y; // magnitude do ray_dir dividida por ray dir_y (semelhança de triângulos) *agora é dividido por 1 para simplificar
		}
		if (game->delta.delta_dist_x[i] < 0)
			game->delta.delta_dist_x[i] = game->delta.delta_dist_x[i] * -1; // transforma nº negativos em positivos
		if (game->delta.delta_dist_y[i] < 0)
			game->delta.delta_dist_y[i] = game->delta.delta_dist_y[i] * -1; // transforma nº negativos em positivos
		//printf("result x: %f\n", game->delta.delta_dist_x[i]);
		//printf("result y: %f\n", game->delta.delta_dist_y[i]);
		//printf("   i: %d\n", i);
		//printf("hypo: %f\n", ray_dir_hypotenuse);
		//printf("rayx: %f\n", game->ray.ray_dir_x[i]);
		//printf("rayy: %f\n", game->ray.ray_dir_y);
		//printf("   x: %f\n", game->delta.delta_dist_x[i]); // prints para testes
		//printf("   y: %f\n", game->delta.delta_dist_y[i]);
	}
}


/*
	Calcula a distância do personagem até a 1ª linha vertical, x.
	Calcula a distância do personagem até a 1ª linha horizontal, y.
*/
void	calc_dist_to_side_x_and_y(t_game *game)
{
	int	i;

	game->dist.dist_to_side_x = malloc((WIDTH + 1) * sizeof(float));
	if (!game->dist.dist_to_side_x)
		exit (EXIT_FAILURE);
	game->dist.dist_to_side_y = malloc((WIDTH + 1) * sizeof(float));
	if (!game->dist.dist_to_side_y)
		exit (EXIT_FAILURE);
	game->dda.step_x = malloc((WIDTH + 1) * sizeof(int));
	if (!game->dda.step_x)
		exit (EXIT_FAILURE);
	game->dda.step_y = malloc((WIDTH + 1) * sizeof(int));
	if (!game->dda.step_y)
		exit (EXIT_FAILURE);
	i = -1;
	while (++i <= WIDTH)
	{
		if (game->ray.ray_dir_x < 0) // Dependendo da direção do raio x, a fórmula muda
		{
			game->dda.step_x[i] = -1;
			game->dist.dist_to_side_x[i] = (game->player.pos[0] \
			- floor(game->player.pos[0])) * game->delta.delta_dist_x[i]; // O floor tira tudo depois do '.' (ex: 5.50510 = 5.00000)
		}
		else
		{
			game->dda.step_x[i] = 1;
			game->dist.dist_to_side_x[i] = (floor(game->player.pos[0]) \
			+ 1 - game->player.pos[0]) * game->delta.delta_dist_x[i];
		}
		if (game->ray.ray_dir_y < 0) // Dependendo da direção do raio y, a fórmula muda
		{
			game->dda.step_y[i] = -1;
			game->dist.dist_to_side_y[i] = (game->player.pos[1] \
			- floor(game->player.pos[1])) * game->delta.delta_dist_y[i];
		}
		else
		{
			game->dda.step_y[i] = 1;
			game->dist.dist_to_side_y[i] = (floor(game->player.pos[1]) \
			+ 1 - game->player.pos[1]) * game->delta.delta_dist_y[i];
		}
		//printf("result: %f\n", floor(game->player.pos[0])); // testes
		//printf("result: %f\n", floor(game->player.pos[1]));
		//printf("result: %f\n", game->dist.dist_to_side_x[i]);
		//printf("result: %f\n", game->dist.dist_to_side_y[i]);
	}
}

/*
	Acha o muro, mas sem calcular a distância.
	Obtemos as coordenadas do personagem até o muro e o lado do quadrado que o raio bateu.
*/
void	dda_find_wall(t_game *game)
{
	int	i;
	int	hit;

	game->dda.hit_side = malloc((WIDTH + 1) * sizeof(float));
	if (!game->dda.hit_side)
		exit (EXIT_FAILURE);
	game->dda.wall_map_pos_x = malloc((WIDTH + 1) * sizeof(float));
	if (!game->dda.wall_map_pos_x)
		exit (EXIT_FAILURE);
	game->dda.wall_map_pos_y = malloc((WIDTH + 1) * sizeof(float));
	if (!game->dda.wall_map_pos_y)
		exit (EXIT_FAILURE);
	game->dda.dda_line_size_x = malloc((WIDTH + 1) * sizeof(float));
	if (!game->dda.dda_line_size_x)
		exit (EXIT_FAILURE);
	game->dda.dda_line_size_y = malloc((WIDTH + 1) * sizeof(float));
	if (!game->dda.dda_line_size_y)
		exit (EXIT_FAILURE);
	i = -1;
	while (++i <= WIDTH)
	{
		hit = FALSE;
		game->dda.dda_line_size_x[i] = game->dist.dist_to_side_x[i]; // O 1º valor sempre será essa distância
		game->dda.dda_line_size_y[i] = game->dist.dist_to_side_y[i]; // O 1º valor sempre será essa distância
		game->dda.wall_map_pos_x[i] = game->player.pos[0];
		game->dda.wall_map_pos_y[i] = game->player.pos[1];
		while (hit != TRUE)
		{
			if (game->dda.dda_line_size_x[i] < game->dda.dda_line_size_y[i])
			{
				game->dda.hit_side[i] = 0; // Na última iteração de i, se entrar nesse if, definirá que o raio bateu no lado vertical
				game->dda.dda_line_size_x[i] += game->delta.delta_dist_x[i];  // Aquele 1º valor + o delta x
				game->dda.wall_map_pos_x[i] += game->dda.step_x[i]; // Itera as coordenadas do mapa horizontalmente (x), um quadrado por vez
			}
			else
			{
				game->dda.hit_side[i] = 1; //Na última iteração de i, se entrar nesse if, definirá que o raio bateu no lado horizontal
				game->dda.dda_line_size_y[i] += game->delta.delta_dist_y[i]; // Aquele 1º valor + o delta y
				game->dda.wall_map_pos_y[i] += game->dda.step_y[i]; // Itera as coordenadas do mapa verticalmente (y), um quadrado por vez
			}
			if (game->map[(int)floor(game->dda.wall_map_pos_y[i])][(int)floor(game->dda.wall_map_pos_x[i])] == '1') // Checa se a coordenada é um muro
				hit = TRUE;
		}
		//printf("hit_side = %d\n", game->dda.hit_side[i]); // testes
	}
}

/*
	Cálculo simplificado que obtem rays perpendiculares ao plano do player,
	protegendo os muros do efeito "olho de peixe"
*/
void	calc_perpendicular_distance(t_game *game)
{
	int	i;

	game->dda.perpendicular_ray = malloc((WIDTH + 1) * sizeof(float));
	if (!game->dda.perpendicular_ray)
		exit (EXIT_FAILURE);
	i = -1;
	while (++i <= WIDTH)
	{
		if (game->dda.hit_side[i] == 0)
		{
			game->dda.perpendicular_ray[i] =
			(game->dda.wall_map_pos_x[i] - game->player.pos[0]
			+ ((1 - game->dda.step_x[i]) / 2)); // Essa fórmula pega a distancia perpendicular do raio até o player para x
			if (game->dda.perpendicular_ray[i] < 0)
				game->dda.perpendicular_ray[i] = game->dda.perpendicular_ray[i] * -1; // Transforma o número em positivo
			game->dda.perpendicular_ray[i] = game->dda.perpendicular_ray[i] / game->ray.ray_dir_x[i]; // trecho final da fórmula
		}
		else
		{
			game->dda.perpendicular_ray[i] =
			(game->dda.wall_map_pos_y[i] - game->player.pos[1]
			+ ((1 - game->dda.step_y[i]) / 2)); //// Essa fórmula pega a distancia perpendicular do raio até o player para y
			if (game->dda.perpendicular_ray[i] < 0)
				game->dda.perpendicular_ray[i] = game->dda.perpendicular_ray[i] * -1; // Transforma o número em positivo
			game->dda.perpendicular_ray[i] = game->dda.perpendicular_ray[i] / game->ray.ray_dir_y; // trecho final da fórmula
		}
		//printf("result = %f\n", game->dda.perpendicular_ray[i]); //testes
	}
}

void	calc_size_lines_to_print(t_game *game)
{
	int		i;
	int		wall_start;
	int		wall_end;
	int		color;

	game->print_line.wall_line_height = malloc((WIDTH + 1) * sizeof(float));
	if (!game->print_line.wall_line_height)
		exit (EXIT_FAILURE);
	i = -1;
	while (++i <= WIDTH)
		game->print_line.wall_line_height[i] = HEIGHT / game->dda.perpendicular_ray[i];
	i = -1;
	while (++i <= WIDTH)
	{
		wall_start = (HEIGHT / 2) - (game->print_line.wall_line_height[i] / 2);
		wall_end = (HEIGHT / 2) + (game->print_line.wall_line_height[i] / 2);
		if (wall_start < 0)
			wall_start = 0;
		if (wall_end >= HEIGHT)
			wall_end = HEIGHT - 1;
/*		color = 0X8B0000; // se comentar das linhas 308 a 312 e descomentar a linha 313 ele printa com texturas ja
		if (game->dda.hit_side[i] == 1)
			color = 0XFF0000;
		while (wall_start < wall_end)
				my_mlx_pixel_put(&game->img, i, wall_start++, color);*/
		print_texture(game, wall_start, wall_end, i);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->img.img_ptr, 0, 0);
}

int	ft_close(t_game *game) // fecha o jogo vai pra exit_utils depois
{
	printf("Bye bye\n");
//	mlx_destroy_window(game->mlx, game->window);
	clean_exit(game);
	return (1);
}

int	game_play(t_game *game)
{
	fill_background(game);
	calc_ray_dir(game);
	calc_delta_dist_x_and_y(game);
	calc_dist_to_side_x_and_y(game);
	dda_find_wall(game);
	calc_perpendicular_distance(game);
	calc_size_lines_to_print(game);
	return (0);
}

void	play_game(t_game *game)
{
	game->mlx = mlx_init();
	get_texture(game);
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.wdt, &game->img.endian);
	game->img.data =  (int *)mlx_get_data_addr(game->img.img_ptr, &game->img.bpp, &game->img.size_l,  &game->img.endian);
	init_player(game);
	mlx_loop_hook(game->mlx, &game_play, game); //roda o jogo em loop
	mlx_key_hook(game->window, &ft_key, game); // verifica tecla foi pressionada
	mlx_hook(game->window, 33, 1L << 17, ft_close, game); // Clicar no X =ESC
	mlx_loop(game->mlx);
}
