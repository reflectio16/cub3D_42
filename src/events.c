/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:22:41 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/11 12:13:52 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void rotation_handler(int keysym, t_game *game)
{
	if (keysym == XK_Left)
	{
		rotate_player(&game->map, -0.05);
		cub_render(&game->mlx, &game->map, game->tile);
	}
	if (keysym == XK_Right)
	{
		rotate_player(&game->map, 0.05);
		cub_render(&game->mlx, &game->map, game->tile);
	}
}

static void	move_handler(int keysym, t_game *game)
{
	if (keysym == XK_w)
	{
		move_forward(&game->map);
		cub_render(&game->mlx, &game->map, game->tile);
	}
	if (keysym == XK_s)
	{
		move_backward(&game->map);
		cub_render(&game->mlx, &game->map, game->tile);
	}
	if (keysym == XK_d)
	{
		move_right(&game->map);
		cub_render(&game->mlx, &game->map, game->tile);
	}
	if (keysym == XK_a)
	{
		move_left(&game->map);
		cub_render(&game->mlx, &game->map, game->tile);
	}
}

int	close_handler(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_connection, mlx->img.img);
	mlx_destroy_window(mlx->mlx_connection, mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_connection);
	free(mlx->mlx_connection);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_handler(&game->mlx);

	rotation_handler(keysym, game);
	move_handler(keysym, game);
	return (0);
}
