/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:22:41 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/26 13:06:10 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotation_handler(t_game *game)
{
	if (game->data.keys.left)
		rotate_player(&game->data, -0.05);
	if (game->data.keys.right)
		rotate_player(&game->data, 0.05);
}

static void	move_handler(t_game *game)
{
	if (game->data.keys.w)
		move_forward(&game->data);
	if (game->data.keys.s)
		move_backward(&game->data);
	if (game->data.keys.d)
		move_right(&game->data);
	if (game->data.keys.a)
		move_left(&game->data);
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
	if (keysym == XK_w)
		game->data.keys.w = 1;
	if (keysym == XK_a)
		game->data.keys.a = 1;
	if (keysym == XK_s)
		game->data.keys.s = 1;
	if (keysym == XK_d)
		game->data.keys.d = 1;
	if (keysym == XK_Left)
		game->data.keys.left = 1;
	if (keysym == XK_Right)
		game->data.keys.right = 1;
	return (0);
}

int	key_release_handler(int keysym, t_game *game)
{
	if (keysym == XK_w)
		game->data.keys.w = 0;
	if (keysym == XK_a)
		game->data.keys.a = 0;
	if (keysym == XK_s)
		game->data.keys.s = 0;
	if (keysym == XK_d)
		game->data.keys.d = 0;
	if (keysym == XK_Left)
		game->data.keys.left = 0;
	if (keysym == XK_Right)
		game->data.keys.right = 0;
	return (0);
}
	
int game_loop(t_game *game)
{
	rotation_handler(game);
	move_handler(game);
	cub_render(&game->mlx, &game->data, game->data.tile);
	return (0);
}
