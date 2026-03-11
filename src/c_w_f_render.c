/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_w_f_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:11:40 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/11 12:21:20 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*choose_current_texture(t_map *map)
{
	t_img	*current_tex;
	current_tex = NULL;
	
	if (map->dda.side == 0 && map->dda.rayDirX > 0)
		current_tex = &map->tex_west;
	else if (map->dda.side == 0 && map->dda.rayDirX < 0)
		current_tex = &map->tex_east;
	else if (map->dda.side == 1 && map->dda.rayDirY < 0)
		current_tex = &map->tex_south;
	else if (map->dda.side == 1 && map->dda.rayDirY > 0)
		current_tex = &map->tex_north;
	return (current_tex);
}

void	draw_ceiling(int y, t_map *map, t_mlx *mlx)
{
	while (y < map->dda.drawStart)
	{
		handle_pixel(map->dda.screenX, y, mlx, ELECTRIC_BLUE);
		y++;
	}
}

void	draw_wall(int x, int y, t_map *map, t_mlx *mlx)
{
	t_img	*current_tex;
	int	color;
	double	step;
	double	texPos;
	int		texY;
	
	color = 0;
	current_tex = choose_current_texture(map);
	step = (double)current_tex->height / map->dda.lineHeight;
	texPos = (map->dda.drawStart - HEIGHT / 2 + map->dda.lineHeight / 2) * step;
	
	map->dda.screenX = x;
	y = map->dda.drawStart;
	while (y < map->dda.drawEnd)
	{
		texY = (int)texPos;
		color = my_mlx_pixel_read(current_tex, map->tex.x, texY);
		handle_pixel(map->dda.screenX, y, mlx, color);
		texPos += step;
		y++;
	}
}

void	draw_floor(int y, t_map *map, t_mlx *mlx)
{
	y = map->dda.drawEnd;
	while (y < HEIGHT)
	{
		handle_pixel(map->dda.screenX, y, mlx, PRUNE);
		y++;
	}
}