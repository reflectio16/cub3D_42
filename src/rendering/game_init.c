/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:44:00 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/14 14:17:36 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	malloc_error(void)
{
	perror("problems with malloc");
	exit(EXIT_FAILURE);
}

void	events_init(t_game *game)
{
	mlx_hook(game->mlx.window, KeyPress, KeyPressMask,
		key_handler, game);
	mlx_hook(game->mlx.window, DestroyNotify, StructureNotifyMask,
		close_handler, game);
}

void	plane_init(t_data *map, double k)
{
	map->player.plane_x = -map->player.dir_y * k;
	map->player.plane_y = map->player.dir_x * k;
}

// void	texture_init(t_data *map)
// {
// 	map->tex.width = ;
// 	map->tex.height = ;

// }

void	cub_init(t_game *game, t_mlx *mlx, t_data *map)
{
	mlx->connection = mlx_init();
	if (mlx->connection == NULL)
		malloc_error();
	mlx->window = mlx_new_window(mlx->connection, WIDTH, HEIGHT, "the_game");
	if (mlx->window == NULL)
	{
		mlx_destroy_display(mlx->connection);
		free(mlx->connection);
		malloc_error();
	}
	mlx->img.img = mlx_new_image(mlx->connection, WIDTH, HEIGHT);
	if (mlx->img.img == NULL)
	{
		mlx_destroy_window(mlx->connection, mlx->window);
		mlx_destroy_display(mlx->connection);
		free(mlx->connection);
		malloc_error();
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
		&mlx->img.bpp,
		&mlx->img.line_len,
		&mlx->img.endian);
	events_init(game);
	load_all_textures(mlx, map);
}
