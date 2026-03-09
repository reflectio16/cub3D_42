/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 13:47:00 by meelma            #+#    #+#             */
/*   Updated: 2026/03/09 16:00:33 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_split(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

t_line_type get_line_type(char *line)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (line[i] == '\n' || line[i] == '\0')
        return (LINE_EMPTY);
    if (ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0
        || ft_strncmp(&line[i], "WE", 2) == 0 || ft_strncmp(&line[i], "EA", 2) == 0)
        return (LINE_TEXTURE);
    else if (ft_strncmp(&line[i], "F", 1) == 0 || ft_strncmp(&line[i], "C", 1) == 0 )
        return (LINE_COLOR);
    if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
            || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
            return (LINE_MAP);
    return (LINE_INVALID);
}

int print_error(char *msg)
{
    printf("Error: %s\n", msg);
    return (-1);
}

void free_data(t_data *data)
{
    if (data->textures.tex_north)
        free(data->textures.tex_north);
    if (data->textures.tex_south)
        free(data->textures.tex_south);
    if (data->textures.tex_west)
        free(data->textures.tex_west);
    if (data->textures.tex_east)
        free(data->textures.tex_east);
    if (data->map)
        free_split(data->map);
}

int clean_exit(int fd, char *line, int ret)
{
    char *tmp;

    free(line);
    while ((tmp = get_next_line(fd)) != NULL)
        free(tmp);
    close(fd);
    return (ret);
}