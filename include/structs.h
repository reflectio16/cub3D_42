/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:00:00 by meelma            #+#    #+#             */
/*   Updated: 2026/03/14 15:01:36 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
** ============== PARSING STRUCTURES ==============
*/

typedef enum e_line_type
{
	LINE_EMPTY = 0,
	LINE_TEXTURE = 1,
	LINE_COLOR = 2,
	LINE_MAP = 3,
	LINE_INVALID = -1
}	t_line_type;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_colors
{
	int		floor;
	int		ceiling;
}	t_colors;

/*
** ============== RENDERING STRUCTURES ==============
*/

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_images
{
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
}	t_images;

typedef struct s_mlx
{
	void	*connection;
	void	*window;
	t_img	img;
}	t_mlx;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_dda
{
	double	pos_x;
	double	pos_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		screen_x;
}	t_dda;

typedef struct s_wall_floor
{
	int		i;
	int		j;
	double	x;
	double	y;
	int		pixel_x;
	int		pixel_y;
}	t_wall_floor;

typedef struct s_player_pixel
{
	double	px;
	double	py;
	int		dx;
	int		dy;
}	t_player_pixel;

typedef struct s_ray
{
	double	camera_x;
	double	x;
	double	y;
}	t_ray;

typedef struct s_contour
{
	int		base_x;
	int		base_y;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
}	t_contour;

typedef struct s_tex
{
	int		x;
	int		y;
	double	wall_x;
	double	wall_y;
	int		width;
	int		height;
}	t_tex;

/*
** ============== MAIN DATA STRUCTURE ==============
*/

typedef struct s_data
{
	char			**map;
	int				map_width;
	int				map_height;
	t_textures		textures;
	t_colors		colors;
	t_images		images;
	t_player		player;
	t_dda			dda;
	t_wall_floor	wf;
	t_player_pixel	player_pixel;
	t_ray			ray;
	t_contour		contour;
	t_tex			tex;
	int				tile;
}	t_data;

typedef struct s_game
{
	t_mlx	mlx;
	t_data	data;
}	t_game;

#endif