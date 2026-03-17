/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:30:10 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/17 15:34:28 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	vertical_or_horizontal(t_data *map)
{
	if (map->dda.side_dist_x < map->dda.side_dist_y)
	{
		map->dda.side_dist_x += map->dda.delta_dist_x;
		map->dda.map_x += map->dda.step_x;
		map->dda.side = 0;
	}
	else
	{
		map->dda.side_dist_y += map->dda.delta_dist_y;
		map->dda.map_y += map->dda.step_y;
		map->dda.side = 1;
	}
}

static int	check_limits(t_data *map)
{
	int	line_len;

	if (map->dda.map_y < 0 || map->dda.map_y >= map->map_height)
		return (1);
	line_len = get_line_width(map, map->dda.map_y);
	if (map->dda.map_x < 0 || map->dda.map_x >= line_len)
		return (1);
	return (0);
}

static void	set_base(int tile, t_data *map)
{
	map->contour.base_x = map->dda.map_x * tile;
	map->contour.base_y = map->dda.map_y * tile;
}

void	dda_draw(int tile, int x, t_data *map, t_mlx *mlx)
{
	int	hit;
	int	y;

	y = 0;
	hit = 0;
	while (hit == 0)
	{
		vertical_or_horizontal(map);
		if (check_limits(map) == 1)
			break ;
		set_base(tile, map);
		if (map->map[map->dda.map_y][map->dda.map_x] == '1')
		{
			set_perp_wall_dist(map);
			if (map->dda.perp_wall_dist <= 0)
				break ;
			set_wall_x(map);
			set_tex_x(map);
			set_wall_height(map);
			draw_ceiling(y, map, mlx);
			draw_wall(x, y, map, mlx);
			draw_floor(y, map, mlx);
			hit = 1;
		}
	}
}
