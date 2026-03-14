/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:00:00 by meelma            #+#    #+#             */
/*   Updated: 2026/03/14 15:02:32 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

/* game_init.c */
void		cub_init(t_game *game, t_mlx *mlx, t_data *data);
void		plane_init(t_data *data, double k);

/* load_texture.c */
void		load_texture(t_mlx *mlx, t_img *texture, char *path);
void		load_all_textures(t_mlx *mlx, t_data *data);

/* render.c */
void		cub_render(t_mlx *mlx, t_data *data, int tile);

/* my_mlx_pxl.c */
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
int			my_mlx_pixel_read(t_img *data, int x, int y);
void		handle_pixel(int x, int y, t_mlx *mlx, int color);

/* events.c */
int			close_handler(t_game *game);
int			key_handler(int keysym, t_game *game);

/* move.c */
void		move_forward(t_data *data);
void		move_backward(t_data *data);
void		move_right(t_data *data);
void		move_left(t_data *data);

/* rotation.c */
void		rotate_player(t_data *data, double rot);

/* dda_debug.c */
void		dda_render(int tile, t_data *data, t_mlx *mlx);
void		dda_debug_ray(int tile, int x, t_data *data, t_mlx *mlx);

/* c_w_f_render.c */
void		draw_ceiling(int y, t_data *data, t_mlx *mlx);
void		draw_wall(int x, int y, t_data *data, t_mlx *mlx);
void		draw_floor(int y, t_data *data, t_mlx *mlx);

/* wall_floor_utils.c */
void		wall_floor_render(int tile, t_mlx *mlx, t_data *data);

/* player_pixel_utils.c */
void		player_pixel_render(int tile, t_data *data, t_mlx *mlx);

/* ray_utils.c */
void		ray_render(int tile, t_data *data, t_mlx *mlx);

/* display_data.c */
void		display_data(t_mlx *mlx, t_data *data);

#endif