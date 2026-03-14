/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:22:41 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/14 14:31:11 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void rotation_handler(int keysym, t_game *game)
{
	if (keysym == XK_Left)
	{
		rotate_player(&game->data, -0.05);
		cub_render(&game->mlx, &game->data, game->data.tile);
	}
	if (keysym == XK_Right)
	{
		rotate_player(&game->data, 0.05);
		cub_render(&game->mlx, &game->data, game->data.tile);
	}
}

static void	move_handler(int keysym, t_game *game)
{
	if (keysym == XK_w)
	{
		move_forward(&game->data);
		cub_render(&game->mlx, &game->data, game->data.tile);
	}
	if (keysym == XK_s)
	{
		move_backward(&game->data);
		cub_render(&game->mlx, &game->data, game->data.tile);
	}
	if (keysym == XK_d)
	{
		move_right(&game->data);
		cub_render(&game->mlx, &game->data, game->data.tile);
	}
	if (keysym == XK_a)
	{
		move_left(&game->data);
		cub_render(&game->mlx, &game->data, game->data.tile);
	}
}

int	close_handler(t_game *game)
{
	mlx_destroy_image(game->mlx.connection, game->data.images.north.img);
	mlx_destroy_image(game->mlx.connection, game->data.images.south.img);
	mlx_destroy_image(game->mlx.connection, game->data.images.west.img);
	mlx_destroy_image(game->mlx.connection, game->data.images.east.img);
	free_data(&game->data);
	mlx_destroy_image(game->mlx.connection, game->mlx.img.img);
	mlx_destroy_window(game->mlx.connection, game->mlx.window);
	mlx_destroy_display(game->mlx.connection);
	free(game->mlx.connection);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_handler(game);

	rotation_handler(keysym, game);
	move_handler(keysym, game);
	return (0);
}
