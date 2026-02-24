/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:57:22 by meelma            #+#    #+#             */
/*   Updated: 2026/02/24 14:03:23 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "defines.h"
# include "parsing.h"
# include "rendering.h"

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     width;
    int     height;
}   t_img;

typedef struct s_data
{
    char    **map;
    int     map_width;
    int     map_height;
    double  player_x;
    double  player_y;
    double  player_angle;
    t_img   tex_north;
    




    
}   t_data;

#endif