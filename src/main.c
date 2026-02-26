/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:58:41 by meelma            #+#    #+#             */
/*   Updated: 2026/02/26 16:05:29 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"

/* ** Helper Functiom for more readable test output.
** Not a part of actual code.
** Will be deleted later on */
static const    char *line_type_to_str(t_line_type type)
{
    if (type == LINE_EMPTY)
        return ("EMPTY");
    else if (type == LINE_TEXTURE)
        return ("TEXTURE");
    else if (type == LINE_COLOR)
        return ("COLOR");
    else if (type == LINE_MAP)
        return ("MAP");
    return ("INVALID");
}

int main(int ac, char** av)
{
    int     fd;
    int     filenamelen;
    char    *line;
    
    if (ac != 2)
    {
        printf("Wrong argument count!");
        return (1);
    }
    filenamelen = ft_strlen(av[1]);
    if (filenamelen < 4 || (ft_strncmp(&av[1][filenamelen - 4], ".cub", 4) != 0))
    {
        printf("Wrong file extention! Must be .cub");
        return (1);
    }
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
       printf("Cannot open the file!");
       return (1);
    }
    while((line = get_next_line(fd)) != NULL)
    {
        printf("Line Type :[%s] %s", line_type_to_str(get_line_type(line)), line);
        free(line);
    }
    close(fd);
    return (0);
}