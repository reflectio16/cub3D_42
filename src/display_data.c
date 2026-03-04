/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:26:10 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/04 18:13:54 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_player_data(t_mlx *mlx, t_map *map)
{
	char buffer[50];

	//   PLAYER POSITION   //
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 30, 30, 0xFFFFFF, "Player position :");
	snprintf(buffer, 50, "(x = %.2f, y = %.2f)", map->player.x, map->player.y);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 45, 45, 0xFFFFFF, buffer);

	//   RAY DIRECTION   //
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 30, 60, 0xFFFFFF, "Last ray direction :");
	snprintf(buffer, 50, "(x = %.2f, y = %.2f)", map->dda.rayDirX, map->dda.rayDirY);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 45, 75, 0xFFFFFF, buffer);

	//   DDA   //
	   // Delta distances
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 30, 90, 0xFFFFFF, "DDA :");
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 45, 105, 0xFFFFFF, "Delta distances :");
	snprintf(buffer, 50, "(x = %.2f, y = %.2f)", map->dda.deltaDistX, map->dda.deltaDistY);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 60, 120, 0xFFFFFF, buffer);
		// Steps
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 45, 135, 0xFFFFFF, "Steps :");
	snprintf(buffer, 50, "(x = %d, y = %d)", map->dda.stepX, map->dda.stepY);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 60, 150, 0xFFFFFF, buffer);
		// Side distances
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 45, 165, 0xFFFFFF, "Side distances :");
	snprintf(buffer, 50, "(x = %.2f, y = %.2f)", map->dda.sideDistX, map->dda.sideDistY);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 60, 180, 0xFFFFFF, buffer);
		// Perp Wall distances
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 45, 195, 0xFFFFFF, "Perp Wall distance :");
	snprintf(buffer, 50, "%.2f", map->dda.perpWallDist);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 60, 210, 0xFFFFFF, buffer);
}

