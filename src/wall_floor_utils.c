/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_floor_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:55:44 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/03 17:02:35 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(int tile, t_map *map, t_mlx *mlx)
{
	map->wf.y = -1;
	while (++map->wf.y < tile)
	{
		map->wf.x = -1;
		while (++map->wf.x < tile)
		{
			map->wf.pixel_x = map->wf.j * tile + map->wf.x;
			map->wf.pixel_y = map->wf.i * tile + map->wf.y;
			handle_pixel(map->wf.pixel_x, map->wf.pixel_y, mlx, 0xDD00FF);
		}
	}
}

void	draw_floor(int tile, t_map *map, t_mlx *mlx)
{
	map->wf.y = -1;
	while (++map->wf.y < tile)
	{
		map->wf.x = -1;
		while (++map->wf.x < tile)
		{
			map->wf.pixel_x = map->wf.j * tile + map->wf.x;
			map->wf.pixel_y = map->wf.i * tile + map->wf.y;
			handle_pixel(map->wf.pixel_x, map->wf.pixel_y, mlx, 0x000000);
		}
	}
}

void	wall_floor_render(int tile, t_mlx *mlx, t_map *map)
{
		
	map->wf.i = 0;
	while (map->map[map->wf.i])
	{
		map->wf.j = 0;
		while (map->map[map->wf.i][map->wf.j])
		{
			if (map->map[map->wf.i][map->wf.j] == '1')
				draw_wall(tile, map, mlx);
			else if (map->map[map->wf.i][map->wf.j] == '0')
				draw_floor(tile, map, mlx);
			map->wf.j++;
		}
		map->wf.i++;
	}
}
