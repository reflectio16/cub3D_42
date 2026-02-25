/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:57:22 by meelma            #+#    #+#             */
/*   Updated: 2026/02/25 14:28:43 by fmoulin          ###   ########.fr       */
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

typedef struct s_data
{
    char    **map;
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
    int     map_width;
    int     map_height;
    double  player_x;
    double  player_y;
    double  player_angle;
	t_img	img;
    t_img   tex_north;
    t_img   tex_south;
    t_img   tex_west;
    t_img   tex_east;
        
}   t_data;

void	map_init(t_data *map);
int		close_handler(t_data *map);
int		key_handler(int keysym, t_data *map);
void	handle_pixel(int x, int y, t_data *map, int color);
void	map_render(t_data *map);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif