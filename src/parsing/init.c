/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:14:48 by meelma            #+#    #+#             */
/*   Updated: 2026/03/14 14:35:34 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_line(char *line, t_data *data, t_list **map_list,
	int *in_map)
{
	if (get_line_type(line) == LINE_TEXTURE)
	{
		if (*in_map)
			return (print_error("Texture path after map"));
		if (parse_texture(line, data) == -1)
			return (-1);
	}
	else if (get_line_type(line) == LINE_COLOR)
	{
		if (*in_map)
			return (print_error("Color path after map"));
		if (parse_color(line, data) == -1)
			return (-1);
	}
	else if (get_line_type(line) == LINE_MAP)
	{
		*in_map = 1;
		add_map_line(line, map_list);
	}
	else if (get_line_type(line) == LINE_EMPTY && *in_map)
		return (print_error("Empty line in map"));
	return (0);
}

int	parse_file(char *filename, t_data *data, t_list **map_list)
{
	int		fd;
	char	*line;
	int		in_map;

	in_map = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error("Cannot open file"));
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (process_line(line, data, map_list, &in_map) == -1)
			return (clean_exit(fd, line, map_list));
		free(line);
	}
	close(fd);
	return (0);
}

static int	validate_textures(t_data *data)
{
	if (!data->textures.north)
		return (print_error("Missing Texture: NO"));
	if (!data->textures.south)
		return (print_error("Missing Texture: SO"));
	if (!data->textures.west)
		return (print_error("Missing texture: WE"));
	if (!data->textures.east)
		return (print_error("Missing texture: EA"));
	return (0);
}

static int	validate_colors(t_data *data)
{
	if (data->colors.floor == -1 || data->colors.ceiling == -1)
		return (print_error("Missing color path"));
	return (0);
}

int	setup_map(t_data *data, t_list *map_list)
{
	data->map = list_to_array(map_list, &data->map_height);
	ft_lstclear(&map_list, NULL);
	if (validate_textures(data) == -1)
		return (-1);
	if (validate_colors(data) == -1)
		return (-1);
	if (!data->map)
		return (print_error("Map is empty"));
	data->map_width = get_map_width(data->map);
	if (validate_map(data) == -1)
		return (-1);
	find_player(data);
	return (0);
}
