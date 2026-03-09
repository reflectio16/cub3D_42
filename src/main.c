/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:58:41 by meelma            #+#    #+#             */
/*   Updated: 2026/03/09 15:53:07 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* ** Helper Functiom for more readable test output.
** Not a part of actual code.
** Will be deleted later on

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
} */

int main(int ac, char **av)
{
    t_data  data;
    t_list  *map_list;

    map_list = NULL;
    ft_memset(&data, 0, sizeof(t_data));
    data.colors.floor_color = -1;
    data.colors.ceiling_color = -1;
    if (check_args(ac, av[1]) == -1)
        return (1);
    if (parse_file(av[1], &data, &map_list) == -1)
    {
        free_data(&data);
        return (1);
    }
    if (setup_map(&data, map_list) == -1)
    {
        free_data(&data);
        return (1);
    }
        
    // Game starting code here

    free_data(&data);
    return (0);
}