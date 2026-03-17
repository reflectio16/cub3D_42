/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 18:30:55 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/17 15:32:34 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ray_init(t_data *map)
{
	map->ray.camera_x = 2 * map->ray.width_x / (double)WIDTH - 1;
	map->ray.step = 0;
	map->ray.previous_map_y = -1;
	map->ray.previous_map_x = -1;
	map->ray.line_len = 0;
	map->ray.x = map->player.dir_x + map->player.plane_x * map->ray.camera_x;
	map->ray.y = map->player.dir_y + map->player.plane_y * map->ray.camera_x;
}

static int	draw_hit_wall_pixel(t_data *map, t_mlx *mlx)
{
	if (map->ray.map_x >= 0 && map->ray.map_x < map->ray.line_len)
	{
		if (map->map[map->ray.map_y][map->ray.map_x] == '1')
		{
			handle_pixel((int)map->wf.x, (int)map->wf.y, mlx, RED);
			return (1);
		}
	}
	else
		return (1);
	return (0);
}

static int	draw_ray_pixel(int tile, t_data *map, t_mlx *mlx)
{
	ray_pixel_position_update(tile, map);
	if (map->ray.map_y >= 0 && map->ray.map_y < map->map_height)
	{
		if (map->ray.previous_map_y != map->ray.map_y)
			map->ray.line_len = get_line_width(map, map->ray.map_y);
		if (draw_hit_wall_pixel(map, mlx) == 1)
			return (1);
	}
	else
		return (1);
	if (map->wf.x >= 0 && map->wf.x < WIDTH && map->wf.y >= 0
		&& map->wf.y < HEIGHT)
	{
		handle_pixel((int)map->wf.x, (int)map->wf.y, mlx, YELLOW);
		draw_tile(tile, map, mlx);
	}
	stock_previous_coordinates(map);
	return (0);
}

void	ray_render(int tile, t_data *map, t_mlx *mlx)
{
	map->ray.l = tile * 100;
	map->ray.width_x = 0;
	while (map->ray.width_x < WIDTH - 1)
	{
		ray_init(map);
		while (map->ray.step < map->ray.l)
		{
			if (draw_ray_pixel(tile, map, mlx) == 1)
				break ;
			map->ray.step++;
		}
		map->ray.width_x++;
	}
}
