/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:19:28 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/17 15:33:01 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_pixel(int x, int y, t_mlx *mlx, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		my_mlx_pixel_put(&mlx->img, x, y, color);
}

void	cub_render(t_mlx *mlx, t_data *map, int tile)
{
	dda_render(tile, map, mlx);
	wall_floor_render(tile, mlx, map);
	player_pixel_render(tile, map, mlx);
	ray_render(tile, map, mlx);
	mlx_put_image_to_window(mlx->connection, mlx->window, mlx->img.img, 0, 0);
}
