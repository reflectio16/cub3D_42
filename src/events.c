/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:22:41 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/05 14:58:24 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_handler(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_connection, mlx->img.img);
	mlx_destroy_window(mlx->mlx_connection, mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_connection);
	free(mlx->mlx_connection);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_mlx *mlx)
{
	if (keysym == XK_Escape)
		close_handler(mlx);

	// manage left and right arrow keys
	// manage W, A, S, and D keys 
	
	// cub_render(map);

	return (0);
}