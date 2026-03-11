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

void	tile_contour_render(int tile, t_map *map, t_mlx *mlx, int color)
{
	map->contour.startX = map->contour.baseX;
	map->contour.startY = map->contour.baseY;
	map->contour.endX = map->contour.baseX + tile - 1;
	map->contour.endY = map->contour.baseY + tile - 1;
	while (map->contour.startX <= map->contour.endX)
	{
		handle_pixel(map->contour.startX, map->contour.startY, mlx, color);
		map->contour.startX++;
	}
	map->contour.startX = map->contour.baseX;
	map->contour.startY = map->contour.baseY;
	while (map->contour.startX <= map->contour.endX)
	{
		handle_pixel(map->contour.startX, map->contour.endY, mlx, color);
		map->contour.startX++;
	}
	map->contour.startX = map->contour.baseX;
	map->contour.startY = map->contour.baseY;
	while (map->contour.startY <= map->contour.endY)
	{
		handle_pixel(map->contour.startX, map->contour.startY, mlx, color);
		map->contour.startY++;
	}
	map->contour.startX = map->contour.baseX;
	map->contour.startY = map->contour.baseY;
	while (map->contour.startY <= map->contour.endY)
	{
		handle_pixel(map->contour.endX, map->contour.startY, mlx, color);
		map->contour.startY++;
	}
}

void	ray_render(int tile, t_map *map, t_mlx *mlx)
{
	int		l;
	int 	step;
	int		x;
	int		mapX;
	int		mapY;
	int		previous_mapX;
	int		previous_mapY;
	int		line_len;

	l = tile * 100;
	x = 0;
	while (x < WIDTH - 1)
	{
		map->ray.camera_x = 2 * x / (double)WIDTH - 1;
		step = 0;
		previous_mapY = -1;
		previous_mapX = -1;
		line_len = 0;
		map->ray.x = map->player.dir_x + map->player.plane_x * map->ray.camera_x;
		map->ray.y = map->player.dir_y + map->player.plane_y * map->ray.camera_x;
		while (step < l)
		{
			
			map->wf.x = map->player_pixel.px + map->ray.x * step;
			map->wf.y = map->player_pixel.py + map->ray.y * step;
			mapX = (int)(map->wf.x / tile);
			mapY = (int)(map->wf.y / tile);
			// mapX et mapY permettent de savoir dans quelle case on est (ex : mapX = 127 / 30 soit 4)
			if (mapY >= 0 && mapY < map->map_height)
			{
				if (previous_mapY != mapY)
					line_len = get_line_width(map, mapY);
				if (mapX >= 0 && mapX < line_len)
				{
					if (map->map[mapY][mapX] == '1')
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
				map->contour.baseX = mapX * tile;
				map->contour.baseY = mapY * tile;
				// baseX et baseY permettent de savoir a quel pixel commence la case (ex : baseX = 4 * 30 soit 120)
				// if (mapX != previous_mapX || mapY != previous_mapY)
				// 	tile_contour_render(tile, map, mlx, BLUE);
			}
			previous_mapX = mapX;
			previous_mapY = mapY;
			step++;
		}
		x++;
	}
}
