/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:26:10 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/11 16:05:45 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_delta_dist(t_data *map)
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

static void	get_step(t_data *map)
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

static void get_side_dist(t_data *map)
{
	if (map->dda.ray_dir_x < 0)
		map->dda.side_dist_x = (map->dda.pos_x - map->dda.map_x) * map->dda.delta_dist_x;
	else
		map->dda.side_dist_x = (map->dda.map_x + 1.0 - map->dda.pos_x) * map->dda.delta_dist_x;

	if (map->dda.ray_dir_y < 0)
		map->dda.side_dist_y = (map->dda.pos_y - map->dda.map_y) * map->dda.delta_dist_y;
	else
		map->dda.side_dist_y = (map->dda.map_y + 1.0 - map->dda.pos_y) * map->dda.delta_dist_y;
}

void	dda_render(int tile, t_data *map, t_mlx *mlx)
{
	int	x;
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
		// En faisant ce cast en (int), si pos_x = 3.5, alors map_x = 3. Normal : tu es dans la case 3.
		
		get_delta_dist(map);
		get_step(map);
		get_side_dist(map);
		dda_debug_ray(tile, x, map, mlx);
		x++;
	}
}

void	get_per_wall_dist(t_data *map)
{
	if (map->dda.side == 0)
		map->dda.perp_wall_dist = (map->dda.map_x - map->dda.pos_x + (1.0 - map->dda.step_x) / 2.0) / map->dda.ray_dir_x;
	else
		map->dda.perp_wall_dist = (map->dda.map_y - map->dda.pos_y + (1.0 - map->dda.step_y) / 2.0) / map->dda.ray_dir_y;
}

void	get_wall_x(t_data *map)
{
	if (map->dda.side == 0)
		map->tex.wall_x = map->dda.pos_y + map->dda.perp_wall_dist * map->dda.ray_dir_y;
	else
		map->tex.wall_x = map->dda.pos_x + map->dda.perp_wall_dist * map->dda.ray_dir_x;
	map->tex.wall_x = map->tex.wall_x - floor(map->tex.wall_x);
}

void	get_tex_x(t_data *map)
{
	map->tex.width = 64;
	map->tex.x = (int)(map->tex.wall_x * map->tex.width);
	if (map->dda.side == 0 && map->dda.ray_dir_x > 0)
		map->tex.x = map->tex.width - map->tex.x - 1;
	if (map->dda.side == 1 && map->dda.ray_dir_y < 0)
		map->tex.x = map->tex.width - map->tex.x - 1; // pourquoi ce calcul ?	
}

void	get_wall_height(t_data *map)
{
	map->dda.line_height = (int)(HEIGHT / map->dda.perp_wall_dist);
	map->dda.draw_start = -map->dda.line_height / 2 + HEIGHT / 2;
	map->dda.draw_end = map->dda.line_height / 2 + HEIGHT / 2;
	if (map->dda.draw_start < 0)
		map->dda.draw_start = 0;
	if (map->dda.draw_end >= HEIGHT)
		map->dda.draw_end = HEIGHT - 1;
}

void	dda_debug_ray(int tile, int x, t_data *map, t_mlx *mlx)
{
	int	hit;
	int	line_len;
	int	y;
	
	y = 0;
	hit = 0;
	while (hit == 0)
	{
		if (map->dda.side_dist_x < map->dda.side_dist_y)
		{
			map->dda.side_dist_x += map->dda.delta_dist_x;
			map->dda.map_x += map->dda.step_x;
			map->dda.side = 0; // frontiere vertical
		}
		else
		{
			map->dda.side_dist_y += map->dda.delta_dist_y;
			map->dda.map_y += map->dda.step_y;
			map->dda.side = 1; // frontiere horizontal
		}
		if (map->dda.map_y < 0 || map->dda.map_y >= map->map_height)
			break ;
		line_len = get_line_width(map, map->dda.map_y);
		if (map->dda.map_x < 0 || map->dda.map_x >= line_len)
			break ;
		map->contour.base_x = map->dda.map_x * tile;
		map->contour.base_y = map->dda.map_y * tile;
		// tile_contour_render(tile, map, mlx, BLUE);
		if (map->map[map->dda.map_y][map->dda.map_x] == '1')
		{
			get_per_wall_dist(map);
			get_wall_x(map);
			get_tex_x(map);
				
			if (map->dda.perp_wall_dist <= 0)
				break ;
			get_wall_height(map);
			draw_ceiling(y, map, mlx);
			draw_wall(x, y, map, mlx);
			draw_floor(y, map, mlx);
			hit = 1;
			// tile_contour_render(tile, map, mlx, RED);
		}
	}
}
