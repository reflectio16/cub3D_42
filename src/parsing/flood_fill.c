/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:39:13 by meelma            #+#    #+#             */
/*   Updated: 2026/03/06 16:35:56 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char    **copy_map(char **map, int height)
{
    char    **copy;
    int     i;

    copy = malloc(sizeof(char *) * (height + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (i < height)
    {
        copy[i] = ft_strdup(map[i]);
        if (!copy[i])
            return (NULL);
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

static int flood_fill(char **map, int x, int y, int height)
{
    if (y < 0 || y >= height || x < 0 || x >= (int)ft_strlen(map[y]))
        return (-1);
    if (map[y][x] == ' ')
        return (-1);
    if (map[y][x] == '1' || map[y][x] == 'V')
        return (0);
    map[y][x] = 'V';
    if (flood_fill(map, x + 1, y, height) == -1) //right
        return (-1);
    if (flood_fill(map, x - 1, y, height) == -1) //left
        return (-1);
    if (flood_fill(map, x, y + 1, height) == -1) //down
        return (-1);
    if (flood_fill(map, x, y - 1, height) == -1) //up
        return (-1);
    return (0);    
}

int check_map_closed(t_data *data)
{
    char    **map_copy;
    int     result;
    int     start_x;
    int     start_y;

    map_copy = copy_map(data->map, data->map_height);
    if (!map_copy)
        return (-1);
    start_x = (int)data->player_x;
    start_y = (int)data->player_y;
    result = flood_fill(map_copy, start_x, start_y, data->map_height);
    free_split(map_copy);
    return (result);
}