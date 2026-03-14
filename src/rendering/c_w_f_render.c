/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_w_f_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:11:40 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/14 14:43:06 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*choose_current_texture(t_data *map)
{
	t_img	*current_tex;
	current_tex = NULL;
	
	if (map->dda.side == 0 && map->dda.ray_dir_x > 0)
		current_tex = &map->images.west;
	else if (map->dda.side == 0 && map->dda.ray_dir_x < 0)
		current_tex = &map->images.east;
	else if (map->dda.side == 1 && map->dda.ray_dir_y < 0)
		current_tex = &map->images.south;
	else if (map->dda.side == 1 && map->dda.ray_dir_y > 0)
		current_tex = &map->images.north;
	return (current_tex);
}

void	draw_ceiling(int y, t_data *map, t_mlx *mlx)
{
	while (y < map->dda.draw_start)
	{
		handle_pixel(map->dda.screen_x, y, mlx, ELECTRIC_BLUE);
		y++;
	}
}

void	draw_wall(int x, int y, t_data *map, t_mlx *mlx)
{
	t_img	*current_tex;
	int	color;
	double	step;
	double	tex_pos;
	int		tex_y;
	
	color = 0;
	current_tex = choose_current_texture(map);
	step = (double)current_tex->height / map->dda.line_height;
	tex_pos = (map->dda.draw_start - HEIGHT / 2 + map->dda.line_height / 2) * step;
	
	map->dda.screen_x = x;
	y = map->dda.draw_start;
	while (y < map->dda.draw_end)
	{
		tex_y = (int)tex_pos;
		color = my_mlx_pixel_read(current_tex, map->tex.x, tex_y);
		handle_pixel(map->dda.screen_x, y, mlx, color);
		tex_pos += step;
		y++;
	}
}

void	draw_floor(int y, t_data *map, t_mlx *mlx)
{
	y = map->dda.draw_end;
	while (y < HEIGHT)
	{
		handle_pixel(map->dda.screen_x, y, mlx, PRUNE);
		y++;
	}
}