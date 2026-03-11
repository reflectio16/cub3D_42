/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:16:13 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/11 16:34:31 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_map *map)
{
	double	newX;
	double	newY;
	double		movespeed;

	movespeed = 0.1;
	newX = map->player.x + map->player.dir_x * movespeed;
	newY = map->player.y + map->player.dir_y * movespeed;
	if (map->map[(int)map->player.y][(int)newX] != '1')
		map->player.x = newX;
	if (map->map[(int)newY][(int)map->player.x] != '1')	
		map->player.y = newY;
}

void	move_backward(t_map *map)
{
	double	newX;
	double	newY;
	double	movespeed;

	movespeed = 0.05;
	newX = map->player.x - map->player.dir_x * movespeed;
	newY = map->player.y - map->player.dir_y * movespeed;
	if (map->map[(int)map->player.y][(int)newX] != '1')
		map->player.x = newX;
	if (map->map[(int)newY][(int)map->player.x] != '1')	
		map->player.y = newY;
}

void	move_right(t_map *map)
{
	double	newX;
	double	newY;
	double	movespeed;

	movespeed = 0.05;
	newX = map->player.x + map->player.plane_x * movespeed;
	newY = map->player.y + map->player.plane_y * movespeed;
	if (map->map[(int)map->player.y][(int)newX] != '1')
		map->player.x = newX;
	if (map->map[(int)newY][(int)map->player.x] != '1')	
		map->player.y = newY;
}

void	move_left(t_map *map)
{
	double	newX;
	double	newY;
	double	movespeed;

	movespeed = 0.05;
	newX = map->player.x - map->player.plane_x * movespeed;
	newY = map->player.y - map->player.plane_y * movespeed;
	if (map->map[(int)map->player.y][(int)newX] != '1')
		map->player.x = newX;
	if (map->map[(int)newY][(int)map->player.x] != '1')	
		map->player.y = newY;
}
