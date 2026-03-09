/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:46:44 by meelma            #+#    #+#             */
/*   Updated: 2026/03/09 15:45:29 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int rgb_to_int(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

static int extract_rgb(char *str)
{
    char    **rgb;
    int     r;
    int     g;
    int     b;
    
    rgb = ft_split(str, ',');
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    free_split(rgb);
    if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255))
        return (rgb_to_int(r, g, b));
    return (-1);
}

int parse_color(char *line, t_data *data)
{
    int i;
    int color;

    i = 1;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    color = extract_rgb(&line[i]);
    if (color == -1)
        return (print_error("Invalid color format"));
    if (line[0] == 'F')
    {
        if (data->colors.floor_color != -1)
            return (print_error("Duplicate color path"));
        data->colors.floor_color = color;
    }
    else if (line[0] == 'C')
    {
        if (data->colors.ceiling_color != -1)
            return (print_error("Duplicate color path"));
        data->colors.ceiling_color = color;
    }    
    return (0);
}

