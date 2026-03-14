/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:26:22 by meelma            #+#    #+#             */
/*   Updated: 2026/03/14 14:27:23 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	assign_texture(char **tex, char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(&path[len - 4], ".xpm", 4) != 0)
		return (print_error("Invalid texture extention"));
	if (*tex != NULL)
	{
		free(path);
		print_error("Duplicate texture");
		return (-1);
	}
	*tex = path;
	return (0);
}

static int	validate_texture_path(char *path)
{
	int	len;
	int	fd;
	
	if (!path || path[0] == '\0')
		return (print_error("Empty texture path"));
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(&path[len - 4], ".xpm", 4) != 0)
		return (print_error("Invalid texture extension"));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("Texture file not found"));
	close(fd);
	return (0); 
}

int	parse_texture(char *line, t_data *data)
{
	int		i;
	int		len;
	char	*path;

	if (!(get_line_type(line) == LINE_TEXTURE))
		return (-1);
	i = 2;
	len = ft_strlen(line);
	if (line[i] != ' ' && line[i] != '\t')
		return (print_error("Invalid texture format"));
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	path = ft_substr(line, i, len - i - 1);
	if (validate_texture_path(path) == -1)
		return (free(path), -1);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (assign_texture(&data->textures.north, path));
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (assign_texture(&data->textures.south, path));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (assign_texture(&data->textures.west, path));
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (assign_texture(&data->textures.east, path));
	return (free(path), -1);
}
