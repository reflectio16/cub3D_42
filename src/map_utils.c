/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:51:25 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/04 17:50:04 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		get_max_height(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
		i++;
	map->map_height = i;
}

static void		get_max_width(t_map	*map)
{
	int	i;
	int	j;

	map->map_width = 0;
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j] != '\n' && map->map[i][j] != '\0')
		{
			j++;
		}
		if (j > map->map_width)
			map->map_width = j;
		i++;
	}
}

int	get_line_width(t_map *map, int current_line)
{
	int j;

	j = 0;
	while (map->map[current_line][j] != '\n' && map->map[current_line][j] != '\0')
		j++;
	return (j);
}

void	map_alloc(t_map *map, int fd)
{
	char	*line;
	int len;

	len = 0;
	while ((line = get_next_line(fd)))
	{
		len++; 
		free(line);
	}
	map->map = malloc(sizeof(char*) * (len + 1));
}

void	get_map(t_map *map, int fd)
{
	char	*line;
	int	i;
	
	i = 0;
	while ((line = get_next_line(fd)))
	{
		map->map[i] = line;
		i++; 
	}
	map->map[i] = NULL;
	get_max_height(map);
	get_max_width(map);
}
