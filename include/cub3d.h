/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:57:22 by meelma            #+#    #+#             */
/*   Updated: 2026/02/26 17:52:36 by fmoulin          ###   ########.fr       */
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

typedef struct s_map
{
    char    **map;
    int     map_width;
    int     map_height;
	t_player	player;
    t_img   tex_north;
    t_img   tex_south;
    t_img   tex_west;
    t_img   tex_east;
        
}   t_map;

void	cub_init(t_mlx *mlx, t_map *map);
void	map_init(t_map *map);
void	player_init(t_map *map);
int		close_handler(t_mlx *mlx);
int		key_handler(int keysym, t_mlx *mlx);
void	handle_pixel(int x, int y, t_mlx *mlx, int color);
void	map_render(t_mlx *mlx, t_map *map);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif