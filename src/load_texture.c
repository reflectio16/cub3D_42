/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 18:50:00 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/10 13:57:55 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_mlx *mlx, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(mlx->mlx_connection, path, &texture->width, &texture->height);
	if (texture->img == 0)
	{
		ft_printf("no texture img detected\n");
		exit(EXIT_FAILURE);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
	if (texture->addr == 0)
	{
		ft_printf("no texture addr detected\n");
		exit(EXIT_FAILURE);
	}
}

void load_all_textures(t_mlx *mlx, t_map *map)
{
    load_texture(mlx, &map->tex_north, "./textures/north.xpm");
    load_texture(mlx, &map->tex_south, "./textures/south.xpm");
    load_texture(mlx, &map->tex_west, "./textures/west.xpm");
    load_texture(mlx, &map->tex_east, "./textures/east.xpm");
}
