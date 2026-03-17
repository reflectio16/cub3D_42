/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:26:10 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/17 15:21:52 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_delta_dist(t_data *map)
{
	if (map->dda.ray_dir_x == 0)
		map->dda.delta_dist_x = 1e30;
	else
		map->dda.delta_dist_x = fabs(1.0 / map->dda.ray_dir_x);
	if (map->dda.ray_dir_y == 0)
		map->dda.delta_dist_y = 1e30;
	else
		map->dda.delta_dist_y = fabs(1.0 / map->dda.ray_dir_y);
}

static void	set_step(t_data *map)
{
	if (map->dda.ray_dir_x < 0)
		map->dda.step_x = -1;
	else
		map->dda.step_x = 1;
	if (map->dda.ray_dir_y < 0)
		map->dda.step_y = -1;
	else
		map->dda.step_y = 1;
}

static void	set_side_dist(t_data *map)
{
	if (map->dda.ray_dir_x < 0)
		map->dda.side_dist_x = (map->dda.pos_x - map->dda.map_x)
			* map->dda.delta_dist_x;
	else
		map->dda.side_dist_x = (map->dda.map_x + 1.0 - map->dda.pos_x)
			* map->dda.delta_dist_x;
	if (map->dda.ray_dir_y < 0)
		map->dda.side_dist_y = (map->dda.pos_y - map->dda.map_y)
			* map->dda.delta_dist_y;
	else
		map->dda.side_dist_y = (map->dda.map_y + 1.0 - map->dda.pos_y)
			* map->dda.delta_dist_y;
}

void	dda_render(int tile, t_data *map, t_mlx *mlx)
{
	int		x;
	double	camera_x;

	x = 0;
	while (x < WIDTH - 1)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		map->dda.pos_x = map->player.x;
		map->dda.pos_y = map->player.y;
		map->dda.ray_dir_x = map->player.dir_x + map->player.plane_x * camera_x;
		map->dda.ray_dir_y = map->player.dir_y + map->player.plane_y * camera_x;
		map->dda.map_x = (int)map->dda.pos_x;
		map->dda.map_y = (int)map->dda.pos_y;
		set_delta_dist(map);
		set_step(map);
		set_side_dist(map);
		dda_draw(tile, x, map, mlx);
		x++;
	}
}
