/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 17:11:38 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/17 15:32:47 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_pixel_position_update(int tile, t_data *map)
{
	map->wf.x = map->player_pixel.px + map->ray.x * map->ray.step;
	map->wf.y = map->player_pixel.py + map->ray.y * map->ray.step;
	map->ray.map_x = (int)(map->wf.x / tile);
	map->ray.map_y = (int)(map->wf.y / tile);
}

void	draw_tile(int tile, t_data *map, t_mlx *mlx)
{
	map->contour.base_x = map->ray.map_x * tile;
	map->contour.base_y = map->ray.map_y * tile;
	if (map->ray.map_x != map->ray.previous_map_x
		|| map->ray.map_y != map->ray.previous_map_y)
		tile_contour_render(tile, map, mlx, BLUE);
}

void	stock_previous_coordinates(t_data *map)
{
	map->ray.previous_map_x = map->ray.map_x;
	map->ray.previous_map_y = map->ray.map_y;
}
