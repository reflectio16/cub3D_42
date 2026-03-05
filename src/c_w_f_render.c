/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_w_f_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:11:40 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/05 16:46:18 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(int y, t_map *map, t_mlx *mlx)
{
	while (y < map->dda.drawStart)
	{
		handle_pixel(map->dda.screenX, y, mlx, ELECTRIC_BLUE);
		y++;
	}
}

void	draw_wall(int x, int y, t_map *map, t_mlx *mlx)
{
	int	shade;
	int	color;

	shade = map->tex.x * 255 / (map->tex.width - 1);
	color = 0;
	if (map->dda.side == 0)
	{
		map->dda.screenX = x;
		y = map->dda.drawStart;
		while (y < map->dda.drawEnd)
		{
			color = (shade << 16);
			handle_pixel(map->dda.screenX, y, mlx, color);
			y++;
		}
	}
	else
	{
		map->dda.screenX = x;
		y = map->dda.drawStart;
		while (y < map->dda.drawEnd)
		{
			color = (shade << 8);
			handle_pixel(map->dda.screenX, y, mlx, color);
			y++;
		}
	}
}

void	draw_floor(int y, t_map *map, t_mlx *mlx)
{
	y = map->dda.drawEnd;
	while (y < HEIGHT)
	{
		handle_pixel(map->dda.screenX, y, mlx, SAPPHIRE);
		y++;
	}
}