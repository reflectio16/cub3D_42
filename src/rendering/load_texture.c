/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 18:50:00 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/14 14:54:34 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_mlx *mlx, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(mlx->connection, path, &texture->width, &texture->height);
	if (texture->img == 0)
	{
		print_error("No texture img detected\n");
		exit(EXIT_FAILURE);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
	if (texture->addr == 0)
	{
		print_error("No texture addr detected\n");
		exit(EXIT_FAILURE);
	}
}

void load_all_textures(t_mlx *mlx, t_data *data)
{
    load_texture(mlx, &data->images.north, data->textures.north);
    load_texture(mlx, &data->images.south, data->textures.south);
    load_texture(mlx, &data->images.west, data->textures.west);
    load_texture(mlx, &data->images.east, data->textures.east);
}
