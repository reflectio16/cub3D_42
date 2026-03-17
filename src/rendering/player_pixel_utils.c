/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pixel_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:39:31 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/17 15:23:23 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_pixel_render(int tile, t_data *map, t_mlx *mlx)
{
	map->player_pixel.px = map->player.x * tile;
	map->player_pixel.py = map->player.y * tile;
	map->player_pixel.dx = -1;
	while (map->player_pixel.dx < 1)
	{
		map->player_pixel.dy = -1;
		while (map->player_pixel.dy < 1)
		{
			handle_pixel((int)(map->player_pixel.px + map->player_pixel.dx),
				(int)(map->player_pixel.py + map->player_pixel.dy), mlx,
				YELLOW);
			map->player_pixel.dy++;
		}
		map->player_pixel.dx++;
	}
}
