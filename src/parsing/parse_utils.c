/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:47:00 by meelma            #+#    #+#             */
/*   Updated: 2026/03/14 14:22:38 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_line_width(t_data *data, int current_line)
{
	int	j;

	j = 0;
	while (data->map[current_line][j] != '\n'
		&& data->map[current_line][j] != '\0')
		j++;
	return (j);
}

t_line_type	get_line_type(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (LINE_EMPTY);
	if (ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0
		|| ft_strncmp(&line[i], "WE", 2) == 0
		|| ft_strncmp(&line[i], "EA", 2) == 0)
		return (LINE_TEXTURE);
	else if (ft_strncmp(&line[i], "F", 1) == 0
		|| ft_strncmp(&line[i], "C", 1) == 0)
		return (LINE_COLOR);
	if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
		|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		return (LINE_MAP);
	return (LINE_INVALID);
}

int	print_error(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	return (-1);
}

