/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:33:30 by meelma            #+#    #+#             */
/*   Updated: 2026/03/06 16:41:23 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int validate_map_chars(char **map)
{
    int row;
    int col;

    row = 0;
    while (map[row])
    {
        col = 0;
        while (map[row][col])
        {
            if (map[row][col] != '0' && map[row][col] != '1' && map[row][col] != ' '
                && map[row][col] != 'N' && map[row][col] != 'S'
                    && map[row][col] != 'E' && map[row][col] != 'W')
                return (-1);
            col++;
        }
        row++;
    }
    return (0);
}

static int count_players(char **map)
{
    int row;
    int col;
    int count;

    count = 0;
    row = 0;
    while (map[row])
    {
        col = 0;
        while (map[row][col])
        {
            if (map[row][col] == 'N' || map[row][col] == 'S'
                || map[row][col] == 'E' || map[row][col] == 'W')
                count++;
            col++;
        }
        row++;
    }
    return (count);
}

int validate_map(t_data *data)
{
    if (!data->map)
        return (-1);
    if (validate_map_chars(data->map) == -1)
        return (-1);
    if (count_players(data->map) != 1)
        return (-1);
    if (check_map_closed(data) == -1)
        return (-1);
    return (0);
}