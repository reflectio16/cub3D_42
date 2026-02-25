/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:19:28 by fmoulin           #+#    #+#             */
/*   Updated: 2026/02/25 15:45:18 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_pixel(int x, int y, t_data *map, int color)
{
		my_mlx_pixel_put(&map->img, x, y, color);		
}

void	map_render(t_data *map)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	pixel_x;
	int	pixel_y;
	int	tile;
	
	tile = 30;
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
						handle_pixel(pixel_x, pixel_y, map, 0x44FF00);
					}
				}
			}
			if (map->map[i][j] == '0')
			{
				y = -1;
				while (++y < tile)
				{
					x = -1;
					while (++x < tile)
					{
						pixel_x = j * tile + x;
						pixel_y = i * tile + y;
						handle_pixel(pixel_x, pixel_y, map, 0x6669FF);
					}
				}
			}
			if (map->map[i][j] == 'N'
				|| map->map[i][j] == 'S'
				|| map->map[i][j] == 'E'
				|| map->map[i][j] == 'W')
			{
				y = -1;
				while (++y < tile)
				{
					x = -1;
					while (++x < tile)
					{
						pixel_x = j * tile + x;
						pixel_y = i * tile + y;
						handle_pixel(pixel_x, pixel_y, map, 0xFF0000);
					}
				}
			}
			j++;
		}
		i++;
	}
	
	// int			x;
	// int			y;

	// y = -1;
	// while (++y < HEIGHT)
	// {
	// 	x = -1;
	// 	while (++x < WIDTH)
	// 	{
	// 		if (y % 2 == 0)
	// 			handle_pixel(x, y, map, 0xFF0000);
	// 		else
	// 		{
	// 			handle_pixel(x, y, map, 0x0000FF);
	// 		}
	// 	}
	// }
	mlx_put_image_to_window(map->mlx_connection,
		map->mlx_window, map->img.img, 0, 0);
}
