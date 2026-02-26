/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:44:00 by fmoulin           #+#    #+#             */
/*   Updated: 2026/02/26 18:21:43 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	malloc_error(void)
{
	perror("problems with malloc");
	exit(EXIT_FAILURE);
}

void	events_init(t_mlx *mlx)
{
	mlx_hook(mlx->mlx_window, KeyPress, KeyPressMask,
		key_handler, mlx);
	mlx_hook(mlx->mlx_window, DestroyNotify, StructureNotifyMask,
		close_handler, mlx);
}

void	map_init(t_map *map)
{
	*map = (t_map){0};
}

void	position_init(t_map *map, int i, int j)
{
	map->player.x = j + 0.5;
	map->player.y = i + 0.5;
}

void	direction_init(t_map *map, int i, int j)
{
	if (map->map[i][j] == 'N')
	{
		map->player.dir_x = 0;
		map->player.dir_y = -1;
	}
	else if (map->map[i][j] == 'S')
	{
		map->player.dir_x = 0;
		map->player.dir_y = 1;
	}
	else if (map->map[i][j] == 'E')
	{
		map->player.dir_x = 1;
		map->player.dir_y = 0;
	}
	else if (map->map[i][j] == 'W')
	{
		map->player.dir_x = -1;
		map->player.dir_y = 0;
	}
}

void	plane_init(t_map *map, double k)
{
	map->player.plane_x = -map->player.dir_y * k;
	map->player.plane_y = map->player.dir_x * k;
}

void	player_init(t_map *map)
{
	int	i;
	int	j;
	double k;
	
	k = 0.66;
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N'
				|| map->map[i][j] == 'S'
				|| map->map[i][j] == 'E'
				|| map->map[i][j] == 'W')
			{
				position_init(map, i, j);
				direction_init(map, i, j);
				plane_init(map, k);
				map->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	cub_init(t_mlx *mlx, t_map *map)
{
	mlx->mlx_connection = mlx_init();
	if (mlx->mlx_connection == NULL)
		malloc_error();
	mlx->mlx_window = mlx_new_window(mlx->mlx_connection, WIDTH, HEIGHT, "the_game");
	if (mlx->mlx_window == NULL)
	{
		mlx_destroy_display(mlx->mlx_connection);
		free(mlx->mlx_connection);
		malloc_error();
	}
	mlx->img.img = mlx_new_image(mlx->mlx_connection, WIDTH, HEIGHT);
	if (mlx->img.img == NULL)
	{
		mlx_destroy_window(mlx->mlx_connection, mlx->mlx_window);
		mlx_destroy_display(mlx->mlx_connection);
		free(mlx->mlx_connection);
		malloc_error();
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
		&mlx->img.bpp,
		&mlx->img.line_len,
		&mlx->img.endian);
	events_init(mlx);
	
	map_init(map);
}