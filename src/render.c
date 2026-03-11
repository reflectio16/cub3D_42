/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:19:28 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/11 14:38:15 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_pixel(int x, int y, t_mlx *mlx, int color)
{
		my_mlx_pixel_put(&mlx->img, x, y, color);		
}

void	cub_render(t_mlx *mlx, t_map *map, int tile)
{
	// dda render
	dda_render(tile, map, mlx);
	
	// minimap wall_floor render
	wall_floor_render(tile, mlx, map);

	// minimap player position pixel filling
	player_pixel_render(tile, map, mlx);
	
	// minimap ray render
	ray_render(tile, map, mlx);
	
	// image on screen
	mlx_put_image_to_window(mlx->mlx_connection,
		mlx->mlx_window, mlx->img.img, 0, 0);
	
	// data written on screen	
	display_data(mlx, map);
}
