/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:16:13 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/14 14:25:34 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_data *map)
{
	double	new_x;
	double	new_y;
	double		movespeed;

	movespeed = 0.1;
	new_x = map->player.x + map->player.dir_x * movespeed;
	new_y = map->player.y + map->player.dir_y * movespeed;
	if (map->map[(int)map->player.y][(int)new_x] != '1')
		map->player.x = new_x;
	if (map->map[(int)new_y][(int)map->player.x] != '1')	
		map->player.y = new_y;
}

void	move_backward(t_data *map)
{
	double	new_x;
	double	new_y;
	double	movespeed;

	movespeed = 0.1;
	new_x = map->player.x - map->player.dir_x * movespeed;
	new_y = map->player.y - map->player.dir_y * movespeed;
	if (map->map[(int)map->player.y][(int)new_x] != '1')
		map->player.x = new_x;
	if (map->map[(int)new_y][(int)map->player.x] != '1')	
		map->player.y = new_y;
}

void	move_right(t_data *map)
{
	double	new_x;
	double	new_y;
	double	movespeed;

	movespeed = 0.1;
	new_x = map->player.x + map->player.plane_x * movespeed;
	new_y = map->player.y + map->player.plane_y * movespeed;
	if (map->map[(int)map->player.y][(int)new_x] != '1')
		map->player.x = new_x;
	if (map->map[(int)new_y][(int)map->player.x] != '1')	
		map->player.y = new_y;
}

void	move_left(t_data *map)
{
	double	new_x;
	double	new_y;
	double	movespeed;

	movespeed = 0.1;
	new_x = map->player.x - map->player.plane_x * movespeed;
	new_y = map->player.y - map->player.plane_y * movespeed;
	if (map->map[(int)map->player.y][(int)new_x] != '1')
		map->player.x = new_x;
	if (map->map[(int)new_y][(int)map->player.x] != '1')	
		map->player.y = new_y;
}
