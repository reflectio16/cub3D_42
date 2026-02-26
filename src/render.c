/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:19:28 by fmoulin           #+#    #+#             */
/*   Updated: 2026/02/26 19:47:59 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_pixel(int x, int y, t_mlx *mlx, int color)
{
		my_mlx_pixel_put(&mlx->img, x, y, color);		
}

void	map_render(t_mlx *mlx, t_map *map)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		pixel_x;
	int		pixel_y;
	int		tile;
	double	px;
	double	py;
	int		dx;
	int		dy;
	int		l;
	
	// map pixel filling
	tile = 30;
	l = tile * 10;
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '1')
			{
				y = -1;
				while (++y < tile)
				{
					x = -1;
					while (++x < tile)
					{
						pixel_x = j * tile + x;
						pixel_y = i * tile + y;
						handle_pixel(pixel_x, pixel_y, mlx, 0xDD00FF);
					}
				}
			}
			else if (map->map[i][j] == '0')
			{
				y = -1;
				while (++y < tile)
				{
					x = -1;
					while (++x < tile)
					{
						pixel_x = j * tile + x;
						pixel_y = i * tile + y;
						handle_pixel(pixel_x, pixel_y, mlx, 0x000000);
					}
				}
			}
			j++;
		}
		i++;
	}

	// player position pixel filling
	px = map->player.x * tile;
	py = map->player.y * tile;
	dx = -3;
	while (dx < 3)
	{
		dy = -3;
		while (dy < 3)
		{
			handle_pixel((int)(px + dx), (int) (py + dy), mlx, 0xFFEE00);
			dy++;
		}
		dx++;
	}

	// directional arrow

	int t = 0;
	while (t < l)
	{
		x = px + map->player.dir_x * t;
		y = py + map->player.dir_y * t;
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			handle_pixel(x, y, mlx, 0xFFEE00);
		t++;
	}	
	// image on screen
	mlx_put_image_to_window(mlx->mlx_connection,
		mlx->mlx_window, mlx->img.img, 0, 0);
}
