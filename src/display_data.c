/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:26:10 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/03 17:32:09 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_player_data(t_mlx *mlx, t_map *map)
{
	char buffer[50];
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 30, 30, 0xFFFFFF, "Player position :");
	snprintf(buffer, 50, "X: %f", map->player.x);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 45, 45, 0xFFFFFF, buffer);
	snprintf(buffer, 50, "Y: %f", map->player.y);
	mlx_string_put(mlx->mlx_connection, mlx->mlx_window, 45, 60, 0xFFFFFF, buffer);

	// printf("deltaDistX : %f\n", map->dda.deltaDistX);
	// printf("deltaDistY : %f\n", map->dda.deltaDistY);
	// printf("stepX : %d\n", map->dda.stepX);
	// printf("stepY : %d\n", map->dda.stepY);
	// printf("sideDistX : %f\n", map->dda.sideDistX);
	// printf("sideDistY : %f\n", map->dda.sideDistY);
}

