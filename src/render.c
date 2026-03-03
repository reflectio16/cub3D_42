/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:19:28 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/03 17:31:18 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_pixel(int x, int y, t_mlx *mlx, int color)
{
		my_mlx_pixel_put(&mlx->img, x, y, color);		
}

void	map_render(t_mlx *mlx, t_map *map, int tile)
{
	// t_wall_floor	wf;
	// t_player_pixel	player_pixel;
	// t_ray			ray;
	
	// wall_floor_init(&wf);
	wall_floor_render(tile, mlx, map);

	// player position pixel filling
	// player_pixel_init(&player_pixel);
	player_pixel_render(tile, map, mlx);

	// directional arrow
	// ray_init(&ray);
	ray_render(tile, map, mlx);
	
	// dda render
	dda_debug_center(map);

	// image on screen
	mlx_put_image_to_window(mlx->mlx_connection,
		mlx->mlx_window, mlx->img.img, 0, 0);
	
	display_player_data(mlx, map);
}
