/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 17:11:38 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/11 15:19:10 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tile_contour_render(int tile, t_data *map, t_mlx *mlx, int color)
{
	map->contour.start_x = map->contour.base_x;
	map->contour.start_y = map->contour.base_y;
	map->contour.end_x = map->contour.base_x + tile - 1;
	map->contour.end_y = map->contour.base_y + tile - 1;
	while (map->contour.start_x <= map->contour.end_x)
	{
		handle_pixel(map->contour.start_x, map->contour.start_y, mlx, color);
		map->contour.start_x++;
	}
	map->contour.start_x = map->contour.base_x;
	map->contour.start_y = map->contour.base_y;
	while (map->contour.start_x <= map->contour.end_x)
	{
		handle_pixel(map->contour.start_x, map->contour.end_y, mlx, color);
		map->contour.start_x++;
	}
	map->contour.start_x = map->contour.base_x;
	map->contour.start_y = map->contour.base_y;
	while (map->contour.start_y <= map->contour.end_y)
	{
		handle_pixel(map->contour.start_x, map->contour.start_y, mlx, color);
		map->contour.start_y++;
	}
	map->contour.start_x = map->contour.base_x;
	map->contour.start_y = map->contour.base_y;
	while (map->contour.start_y <= map->contour.end_y)
	{
		handle_pixel(map->contour.end_x, map->contour.start_y, mlx, color);
		map->contour.start_y++;
	}
}

void	ray_render(int tile, t_data *map, t_mlx *mlx)
{
	int		l;
	int 	step;
	int		x;
	int		map_x;
	int		map_y;
	int		previous_map_x;
	int		previous_map_y;
	int		line_len;

	l = tile * 100;
	x = 0;
	while (x < WIDTH - 1)
	{
		map->ray.camera_x = 2 * x / (double)WIDTH - 1;
		step = 0;
		previous_map_y = -1;
		previous_map_x = -1;
		line_len = 0;
		map->ray.x = map->player.dir_x + map->player.plane_x * map->ray.camera_x;
		map->ray.y = map->player.dir_y + map->player.plane_y * map->ray.camera_x;
		while (step < l)
		{
			
			map->wf.x = map->player_pixel.px + map->ray.x * step;
			map->wf.y = map->player_pixel.py + map->ray.y * step;
			map_x = (int)(map->wf.x / tile);
			map_y = (int)(map->wf.y / tile);
			// map_x et map_y permettent de savoir dans quelle case on est (ex : map_x = 127 / 30 soit 4)
			if (map_y >= 0 && map_y < map->map_height)
			{
				if (previous_map_y != map_y)
					line_len = get_line_width(map, map_y);
				if (map_x >= 0 && map_x < line_len)
				{
					if (map->map[map_y][map_x] == '1')
					{
						handle_pixel((int)map->wf.x, (int)map->wf.y, mlx, 0xFF0000);
						break ;
					}
				}
				else
					break ;
			}
			else
				break ;
			if (map->wf.x >= 0 && map->wf.x < WIDTH && map->wf.y >= 0 && map->wf.y < HEIGHT)
			{
				handle_pixel((int)map->wf.x, (int)map->wf.y, mlx, 0xFFEE00);
				map->contour.base_x = map_x * tile;
				map->contour.base_y = map_y * tile;
				// base_x et base_y permettent de savoir a quel pixel commence la case (ex : base_x = 4 * 30 soit 120)
				// if (map_x != previous_map_x || map_y != previous_map_y)
				// 	tile_contour_render(tile, map, mlx, BLUE);
			}
			previous_map_x = map_x;
			previous_map_y = map_y;
			step++;
		}
		x++;
	}
}
