/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:26:10 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/03 17:29:58 by fmoulin          ###   ########.fr       */
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

void	dda_debug_center(t_map *map)
{
	map->ray.camera_x[0] = 0;
	map->dda.posX = map->player.x;
	map->dda.posY = map->player.y;
	map->dda.rayDirX = map->player.dir_x;
	map->dda.rayDirY = map->player.dir_y;
	map->dda.mapX = (int)map->dda.posX;
	map->dda.mapY = (int)map->dda.posY;
	// En faisant ce cast en (int), si posX = 3.5, alors mapX = 3. Normal : tu es dans la case 3.
	
	get_deltaDist(map);
	get_step(map);
	get_sideDist(map);
	printf("deltaDistX : %f\n", map->dda.deltaDistX);
	printf("deltaDistY : %f\n", map->dda.deltaDistY);
	printf("stepX : %d\n", map->dda.stepX);
	printf("stepY : %d\n", map->dda.stepY);
	printf("sideDistX : %f\n", map->dda.sideDistX);
	printf("sideDistY : %f\n", map->dda.sideDistY);
}
