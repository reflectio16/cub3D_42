/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:39:13 by meelma            #+#    #+#             */
/*   Updated: 2026/03/16 13:35:53 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(char **map, int x, int y, int height)
{
	if (y < 0 || y >= height || x < 0 || x >= (int)ft_strlen(map[y]))
		return (-1);
	if (map[y][x] == '1' || map[y][x] == ' ' || map[y][x] == 'V')
		return (0);
	map[y][x] = 'V';
	if (flood_fill(map, x + 1, y, height) == -1)
		return (-1);
	if (flood_fill(map, x - 1, y, height) == -1)
		return (-1);
	if (flood_fill(map, x, y + 1, height) == -1)
		return (-1);
	if (flood_fill(map, x, y - 1, height) == -1)
		return (-1);
	return (0);
}
