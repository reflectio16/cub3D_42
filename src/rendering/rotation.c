/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:50:16 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/17 15:33:11 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_data *map, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = map->player.dir_x;
	old_plane_x = map->player.plane_x;
	map->player.dir_x = map->player.dir_x * cos(rot) - map->player.dir_y
		* sin(rot);
	map->player.dir_y = old_dir_x * sin(rot) + map->player.dir_y * cos(rot);
	map->player.plane_x = map->player.plane_x * cos(rot) - map->player.plane_y
		* sin(rot);
	map->player.plane_y = old_plane_x * sin(rot) + map->player.plane_y
		* cos(rot);
}
