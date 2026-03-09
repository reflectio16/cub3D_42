/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:26:22 by meelma            #+#    #+#             */
/*   Updated: 2026/03/09 15:25:23 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int  assign_texture(char **tex, char *path)
{
    if (*tex != NULL)
    {
        free(path);
        print_error("Duplicate texture");
        return (-1);
    }
    *tex = path;
    return (0);
}

int parse_texture(char *line, t_data *data)
{
    int     i;
    int     len;
    char    *path;
    
    if (!(get_line_type(line) == LINE_TEXTURE))
        return (-1);
    i = 2;
    len = ft_strlen(line);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    path = ft_substr(line, i, len - i - 1);
    if (!path)
        return (-1);
    if (ft_strncmp(line, "NO", 2) == 0)
        return (assign_texture(&data->textures.tex_north, path));
    else if (ft_strncmp(line, "SO", 2) == 0)
        return (assign_texture(&data->textures.tex_south, path));
    else if (ft_strncmp(line, "WE", 2) == 0)
        return (assign_texture(&data->textures.tex_west, path));
    else if (ft_strncmp(line, "EA", 2) == 0)
        return (assign_texture(&data->textures.tex_east, path));
    return (free(path), -1);  
}

