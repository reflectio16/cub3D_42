/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:57:22 by meelma            #+#    #+#             */
/*   Updated: 2026/03/09 15:27:10 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

//# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
//# include "defines.h"
# include "parsing.h"
//# include "rendering.h"

# include "../Libft/libft.h"
# include "../gnl/get_next_line.h"

# define M_PI 3.14159265358979323846

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
    t_texture textures;
    t_color     colors;
    // rest of the variables

}   t_data;

#endif