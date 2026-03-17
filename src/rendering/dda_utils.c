/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:11:10 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/17 15:22:16 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_perp_wall_dist(t_data *map)
{
	if (map->dda.side == 0)
		map->dda.perp_wall_dist = (map->dda.map_x - map->dda.pos_x + (1.0
					- map->dda.step_x) / 2.0) / map->dda.ray_dir_x;
	else
		map->dda.perp_wall_dist = (map->dda.map_y - map->dda.pos_y + (1.0
					- map->dda.step_y) / 2.0) / map->dda.ray_dir_y;
}

void	set_wall_x(t_data *map)
{
	if (map->dda.side == 0)
		map->tex.wall_x = map->dda.pos_y + map->dda.perp_wall_dist
			* map->dda.ray_dir_y;
	else
		map->tex.wall_x = map->dda.pos_x + map->dda.perp_wall_dist
			* map->dda.ray_dir_x;
	map->tex.wall_x = map->tex.wall_x - floor(map->tex.wall_x);
}

void	set_tex_x(t_data *map)
{
	map->tex.width = 64;
	map->tex.x = (int)(map->tex.wall_x * map->tex.width);
	if (map->dda.side == 0 && map->dda.ray_dir_x > 0)
		map->tex.x = map->tex.width - map->tex.x - 1;
	if (map->dda.side == 1 && map->dda.ray_dir_y < 0)
		map->tex.x = map->tex.width - map->tex.x - 1;
}

void	set_wall_height(t_data *map)
{
	map->dda.line_height = (int)(HEIGHT / map->dda.perp_wall_dist);
	map->dda.draw_start = -map->dda.line_height / 2 + HEIGHT / 2;
	map->dda.draw_end = map->dda.line_height / 2 + HEIGHT / 2;
	if (map->dda.draw_start < 0)
		map->dda.draw_start = 0;
	if (map->dda.draw_end >= HEIGHT)
		map->dda.draw_end = HEIGHT - 1;
}
