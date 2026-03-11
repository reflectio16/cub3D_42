/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:26:10 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/11 16:32:56 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_data(char *buffer, t_mlx *mlx, t_map *map)
{
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1000, 30, 0xFFFFFF, "PLAYER DATAS");

	//   PLAYER POSITION   //
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1030, 45, 0xFFFFFF, "Player position :");
	snprintf(buffer, 50, "(x = %.2f, y = %.2f)", map->player.x, map->player.y);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1045, 60, 0xFFFFFF, buffer);

	//   PLAYER DIRECTION   //
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1030, 75, 0xFFFFFF, "Player direction :");
	snprintf(buffer, 50, "(x = %.2f, y = %.2f)", map->player.dir_x, map->player.dir_y);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1045, 90, 0xFFFFFF, buffer);

	//   PLAYER PLANE   //
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1030, 105, 0xFFFFFF, "Player plane :");
	snprintf(buffer, 50, "(x = %.2f, y = %.2f)", map->player.plane_x, map->player.plane_y);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1045, 120, 0xFFFFFF, buffer);
	
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1030, 135, 0xFF8000, "Plane calculation:");
	snprintf(buffer, 50, "(x = %.2f * 0.66, y = %.2f * 0.66)", -map->player.dir_y, map->player.dir_x);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1045, 150, 0xFFFF00, buffer);
}

static void	ray_data(char *buffer, t_mlx *mlx, t_map *map)
{
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1300, 30, 0xFFFFFF, "RAY DATAS");
	
	//   RAY DIRECTION   //
		// Last ray direction
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1330, 45, 0xFFFFFF, "Last ray direction :");
	snprintf(buffer, 50, "(x = %.2f, y = %.2f)", map->dda.rayDirX, map->dda.rayDirY);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1345, 60, 0xFFFFFF, buffer);
		// CameraX calculation
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1330, 75, 0xFF8000, "CameraX calculation :");
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1345, 90, 0xFFFF00, "Pour x allant de 0 a WIDTH");
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1345, 105, 0xFFFF00, "(pour le dernier rayon : x = WIDTH)");
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1345, 120, 0xFFFF00, "CameraX = 2 * x / WIDTH - 1");
	snprintf(buffer, 50, "2 * %d / %d - 1 = 1", WIDTH, WIDTH);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1345, 135, 0xFFFF00, buffer);
		// Last ray calculation
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1330, 150, 0xFF8000, "Last ray calculation:");
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1345, 165, 0xFFFF00, "dir_x + plane_x * cameraX");
	snprintf(buffer, 50, "x = %.2f + %.2f * %.2f", map->player.dir_x, map->player.plane_x, map->ray.camera_x);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1345, 180, 0xFFFF00, buffer);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1345, 195, 0xFFFF00, "dir_y + plane_y * cameraX");
	snprintf(buffer, 50, "y = %.2f + %.2f * %.2f", map->player.dir_y, map->player.plane_y, map->ray.camera_x);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1345, 210, 0xFFFF00, buffer);
}

static void dda_data(char *buffer, t_mlx *mlx, t_map *map)
{
	//   DDA   //
	   // Delta distances
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1630, 30, 0xFFFFFF, "DDA :");
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1645, 45, 0xFFFFFF, "Delta distances :");
	snprintf(buffer, 50, "(x = %.2f, y = %.2f)", map->dda.deltaDistX, map->dda.deltaDistY);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1660, 60, 0xFFFFFF, buffer);
		// Steps
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1645, 75, 0xFFFFFF, "Steps :");
	snprintf(buffer, 50, "(x = %d, y = %d)", map->dda.stepX, map->dda.stepY);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1660, 90, 0xFFFFFF, buffer);
		// Side distances
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1645, 105, 0xFFFFFF, "Side distances :");
	snprintf(buffer, 50, "(x = %.2f, y = %.2f)", map->dda.sideDistX, map->dda.sideDistY);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1660, 120, 0xFFFFFF, buffer);
		// Perp Wall distances
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1645, 135, 0xFFFFFF, "Perp Wall distance :");
	snprintf(buffer, 50, "%.2f", map->dda.perpWallDist);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 1660, 150, 0xFFFFFF, buffer);
}

void	display_data(t_mlx *mlx, t_map *map)
{
	char 	buffer[10000];

	player_data(buffer, mlx, map);
	ray_data(buffer, mlx, map);
	dda_data(buffer, mlx, map);
}
