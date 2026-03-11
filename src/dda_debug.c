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
	int	x;
	double	cameraX;
	
	x = 0;
	while (x < WIDTH - 1)
	{
		cameraX = 2 * x / (double)WIDTH - 1;
	
	
		map->dda.posX = map->player.x;
		map->dda.posY = map->player.y;
		map->dda.rayDirX = map->player.dir_x + map->player.plane_x * cameraX;
		map->dda.rayDirY = map->player.dir_y + map->player.plane_y * cameraX;
		map->dda.mapX = (int)map->dda.posX;
		map->dda.mapY = (int)map->dda.posY;
		// En faisant ce cast en (int), si posX = 3.5, alors mapX = 3. Normal : tu es dans la case 3.
		
		get_deltaDist(map);
		get_step(map);
		get_sideDist(map);
		dda_debug_ray(tile, x, map, mlx);
		x++;
	}
}

void	get_perWallDist(t_map *map)
{
	if (map->dda.side == 0)
		map->dda.perpWallDist = (map->dda.mapX - map->dda.posX + (1.0 - map->dda.stepX) / 2.0) / map->dda.rayDirX;
	else
		map->dda.perpWallDist = (map->dda.mapY - map->dda.posY + (1.0 - map->dda.stepY) / 2.0) / map->dda.rayDirY;
}

void	get_wallX(t_map *map)
{
	if (map->dda.side == 0)
		map->tex.wallX = map->dda.posY + map->dda.perpWallDist * map->dda.rayDirY;
	else
		map->tex.wallX = map->dda.posX + map->dda.perpWallDist * map->dda.rayDirX;
	map->tex.wallX = map->tex.wallX - floor(map->tex.wallX);
}

void	get_texX(t_map *map)
{
	map->tex.width = 64;
	map->tex.x = (int)(map->tex.wallX * map->tex.width);
	if (map->dda.side == 0 && map->dda.rayDirX > 0)
		map->tex.x = map->tex.width - map->tex.x - 1;
	if (map->dda.side == 1 && map->dda.rayDirY < 0)
		map->tex.x = map->tex.width - map->tex.x - 1; // pourquoi ce calcul ?	
}

void	get_wall_height(t_map *map)
{
	map->dda.lineHeight = (int)(HEIGHT / map->dda.perpWallDist);
	map->dda.drawStart = -map->dda.lineHeight / 2 + HEIGHT / 2;
	map->dda.drawEnd = map->dda.lineHeight / 2 + HEIGHT / 2;
	if (map->dda.drawStart < 0)
		map->dda.drawStart = 0;
	if (map->dda.drawEnd >= HEIGHT)
		map->dda.drawEnd = HEIGHT - 1;
}

void	dda_debug_ray(int tile, int x, t_map *map, t_mlx *mlx)
{
	int	hit;
	int	line_len;
	int	y;
	
	y = 0;
	hit = 0;
	while (hit == 0)
	{
		if (map->dda.sideDistX < map->dda.sideDistY)
		{
			map->dda.sideDistX += map->dda.deltaDistX;
			map->dda.mapX += map->dda.stepX;
			map->dda.side = 0; // frontiere vertical
		}
		else
		{
			map->dda.sideDistY += map->dda.deltaDistY;
			map->dda.mapY += map->dda.stepY;
			map->dda.side = 1; // frontiere horizontal
		}
		if (map->dda.mapY < 0 || map->dda.mapY >= map->map_height)
			break ;
		line_len = get_line_width(map, map->dda.mapY);
		if (map->dda.mapX < 0 || map->dda.mapX >= line_len)
			break ;
		map->contour.baseX = map->dda.mapX * tile;
		map->contour.baseY = map->dda.mapY * tile;
		// tile_contour_render(tile, map, mlx, BLUE);
		if (map->map[map->dda.mapY][map->dda.mapX] == '1')
		{
			get_perWallDist(map);
			get_wallX(map);
			get_texX(map);
				
			if (map->dda.perpWallDist <= 0)
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
