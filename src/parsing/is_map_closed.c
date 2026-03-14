/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 13:06:07 by meelma            #+#    #+#             */
/*   Updated: 2026/03/14 14:14:24 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int  is_walkable(char c)
{
    return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int  check_top_bottom(char **map, int height)
{
    int i;

    i = 0;
    while (map[0][i] && map[0][i] != '\n')
    {
        if (is_walkable(map[0][i]))
            return (-1);
        i++;
    }
    i = 0;
    while (map[height - 1][i] && map[height - 1][i] != '\n')
    {
        if (is_walkable(map[height - 1][i]))
            return (-1);
        i++;
    }
    return (0);
}

static int  check_sides(char **map, int height)
{
    int i;
    int len;

    i = 0;
    while (i < height)
    {
        len = ft_strlen(map[i]);
        if (len > 0 && map[i][len - 1] == '\n')
            len--;
        if (is_walkable(map[i][0]))
            return (-1);
        if (len > 0 && is_walkable(map[i][len -1]))
            return (-1);
        i++;
    }
    return (0);
}

static char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

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

int	check_map_closed(t_data *data)
{
	char	**map_copy;
	int		result;

    if (check_top_bottom(data->map, data->map_height) == -1)
        return (-1);
    if (check_sides(data->map, data->map_height) == -1)
        return (-1);
    map_copy = copy_map(data->map, data->map_height);
	if (!map_copy)
		return (-1);
	result = flood_fill(map_copy, (int)data->player.x,
        (int)data->player.y, data->map_height);
	free_split(map_copy);
	return (result);
}