/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:26:10 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/04 18:34:36 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_deltaDist(t_map *map)
{
	if (map->dda.rayDirX == 0)
		map->dda.deltaDistX = 1e30;
	else
		map->dda.deltaDistX = fabs(1.0 / map->dda.rayDirX);
	
	if (map->dda.rayDirY == 0)
		map->dda.deltaDistY = 1e30;
	else
		map->dda.deltaDistY = fabs(1.0 / map->dda.rayDirY);
}

static void	get_step(t_map *map)
{
	if (map->dda.rayDirX < 0)
		map->dda.stepX = -1;
	else
		map->dda.stepX = 1;
		
	if (map->dda.rayDirY < 0)
		map->dda.stepY = -1;
	else
		map->dda.stepY = 1;
}

static void get_sideDist(t_map *map)
{
	if (map->dda.rayDirX < 0)
		map->dda.sideDistX = (map->dda.posX - map->dda.mapX) * map->dda.deltaDistX;
	else
		map->dda.sideDistX = (map->dda.mapX + 1.0 - map->dda.posX) * map->dda.deltaDistX;

	if (map->dda.rayDirY < 0)
		map->dda.sideDistY = (map->dda.posY - map->dda.mapY) * map->dda.deltaDistY;
	else
		map->dda.sideDistY = (map->dda.mapY + 1.0 - map->dda.posY) * map->dda.deltaDistY;
}

void	dda_render(int tile, t_map *map, t_mlx *mlx)
{
	int i;

	map->ray.camera_x[0] = -0.5;
	map->ray.camera_x[1] = 0;
	map->ray.camera_x[2] = 0.5;

	i = 0;
	while (i < 3)
	{
		map->dda.posX = map->player.x;
		map->dda.posY = map->player.y;
		map->dda.rayDirX = map->player.dir_x + map->player.plane_x * map->ray.camera_x[i];
		map->dda.rayDirY = map->player.dir_y + map->player.plane_y * map->ray.camera_x[i];
		map->dda.mapX = (int)map->dda.posX;
		map->dda.mapY = (int)map->dda.posY;
		// En faisant ce cast en (int), si posX = 3.5, alors mapX = 3. Normal : tu es dans la case 3.
		
		get_deltaDist(map);
		get_step(map);
		get_sideDist(map);
		dda_debug_ray(tile, map, mlx);
		i++;
	}
}

void	dda_debug_ray(int tile, t_map *map, t_mlx *mlx)
{
	int	hit;
	int	line_len;
	
	hit = 0;
	while (hit == 0)
	{
		if (map->dda.sideDistX < map->dda.sideDistY)
		{
			map->dda.sideDistX += map->dda.deltaDistX;
			map->dda.mapX += map->dda.stepX;
			map->dda.side = 0; // mur vertical
		}
		else
		{
			map->dda.sideDistY += map->dda.deltaDistY;
			map->dda.mapY += map->dda.stepY;
			map->dda.side = 1; // mur horizontal
		}
		if (map->dda.mapY < 0 || map->dda.mapY >= map->map_height)
			break ;
		line_len = get_line_width(map, map->dda.mapY);
		if (map->dda.mapX < 0 || map->dda.mapX >= line_len)
			break ;
		map->contour.baseX = map->dda.mapX * tile;
		map->contour.baseY = map->dda.mapY * tile;
		tile_contour_render(tile, map, mlx, BLUE);
		if (map->map[map->dda.mapY][map->dda.mapX] == '1')
		{
			if (map->dda.side == 0)
				map->dda.perpWallDist = (map->dda.mapX - map->dda.posX + (1.0 - map->dda.stepX) / 2.0) / map->dda.rayDirX;
			else
				map->dda.perpWallDist = (map->dda.mapY - map->dda.posY + (1.0 - map->dda.stepY) / 2.0) / map->dda.rayDirY;
			hit = 1;
			tile_contour_render(tile, map, mlx, RED);
		}
	}
}
