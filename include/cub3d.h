/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:57:22 by meelma            #+#    #+#             */
/*   Updated: 2026/03/04 18:34:36 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
// # include "defines.h"
// # include "parsing.h"
// # include "rendering.h"

# define WIDTH 1920
# define HEIGHT 1080

# define BLUE 0x0000FF
# define RED 0xFF0000


typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
	int		endian;
    int     width;
    int     height;
	
}   t_img;

typedef struct s_mlx
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	
}	t_mlx;

typedef struct s_player
{
    double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
        
}   t_player;


typedef struct s_wall_floor
{
	int		i;
	int		j;
	int		x;
	int		y;
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
	double	camera_x[3];
	double	x;
	double	y;
	
}	t_ray;

typedef struct s_contour
{
	int		baseX;
	int		baseY;
	int		startX;
	int		startY;
	int		endX;
	int		endY;
	
}	t_contour;

typedef struct s_dda
{
	double	posX;
	double	posY;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	double	sideDistX;
	double	sideDistY;
	int		side;
	double	perpWallDist;
	
}	t_dda;

typedef struct s_map
{
	char    		**map;
	int     		map_width;
	int     		map_height;
	t_player		player;
	t_wall_floor	wf;
	t_player_pixel	player_pixel;
	t_ray			ray;
	t_contour		contour;
	t_dda			dda;
	t_img   		tex_north;
	t_img   		tex_south;
	t_img   		tex_west;
	t_img   		tex_east;
		
}   t_map;

//   INIT   //
void	cub_init(t_mlx *mlx, t_map *map);
void	map_init(t_map *map);
void	player_init(t_map *map);

//   MEMORY ALLOC   //
void	map_alloc(t_map *map, int fd);

//   GETTERS   //
void	get_map(t_map *map, int fd);
int		get_line_width(t_map *map, int current_line);

//   MLX CTRLS   //
int		close_handler(t_mlx *mlx);
int		key_handler(int keysym, t_mlx *mlx);

//   RENDER   //
void	handle_pixel(int x, int y, t_mlx *mlx, int color);
void	map_render(t_mlx *mlx, t_map *map, int tile);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw_wall(int tile, t_map *map, t_mlx *mlx);
void	draw_floor(int tile, t_map *map, t_mlx *mlx);
void	wall_floor_render(int tile, t_mlx *mlx, t_map *map);
void	player_pixel_render(int tile, t_map *map, t_mlx *mlx);
void	ray_render(int tile, t_map *map, t_mlx *mlx);
void	tile_contour_render(int tile, t_map *map, t_mlx *mlx, int color);

//   DDA   //
void	dda_render(int tile, t_map *map, t_mlx *mlx);
void	dda_debug_ray(int tile, t_map *map, t_mlx *mlx);

//   DISPLAY   //
void	display_player_data(t_mlx *mlx, t_map *map);

#endif