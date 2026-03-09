/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:14:48 by meelma            #+#    #+#             */
/*   Updated: 2026/03/09 16:01:45 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_args(int ac, char *filename)
{
    int len;
    
    if (ac != 2)
        return (print_error("Wrong argument count"));
    len = ft_strlen(filename);
    if (len < 4 || ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
        return (print_error("Wrong file extension. Must be .cub"));
    return (0);
}

int parse_file(char *filename, t_data *data, t_list **map_list)
{
    int     fd;
    char    *line;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (print_error("Cannot open file"));
    while ((line = get_next_line(fd)) != NULL)
    {
        if (get_line_type(line) == LINE_TEXTURE)
        {
          if (parse_texture(line, data) == -1)
            return (clean_exit(fd, line, -1));  
        }
        else if (get_line_type(line) == LINE_COLOR)
        {
            if ( parse_color(line, data) == -1)
                return (clean_exit(fd, line, -1));
        } 
        else if (get_line_type(line) == LINE_MAP)
            add_map_line(line, map_list);
        free(line);
    }
    close(fd);
    return (0);
}

static int  validate_textures(t_data *data)
{
    if (!data->textures.tex_north)
        return (print_error("Missing Texture: NO"));
    if (!data->textures.tex_south)
        return (print_error("Missing Texture: SO"));
    if (!data->textures.tex_west)
        return (print_error("Missing texture: WE"));
    if (!data->textures.tex_east)
        return (print_error("Missing texture: EA"));
    return (0);
}

static int validate_colors(t_data *data)
{
    if (data->colors.floor_color == -1 || data->colors.ceiling_color == -1)
        return (print_error("Missing color path"));
    return (0);
}

int setup_map(t_data *data, t_list *map_list)
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
    find_player(data);
    if (validate_map(data) == -1)
        return (-1);
    return (0);
}