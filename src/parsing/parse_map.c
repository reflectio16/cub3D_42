/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:08:15 by meelma            #+#    #+#             */
/*   Updated: 2026/03/14 14:12:11 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_map_line(char *line, t_list **map_list)
{
	t_list	*node;
	char	*trimmed;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return (-1);
	node = ft_lstnew(trimmed);
	if (!node)
	{
		free(trimmed);
		return (-1);
	}
	ft_lstadd_back(map_list, node);
	return (0);
}

char	**list_to_array(t_list *list, int *height)
{
	char	**arr;
	int		lst_size;
	int		i;

	lst_size = ft_lstsize(list);
	if (lst_size == 0)
		return (NULL);
	arr = malloc(sizeof(char *) * (lst_size + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (list)
	{
		arr[i] = list->content;
		list = list->next;
		i++;
	}
	arr[i] = NULL;
	*height = lst_size;
	return (arr);
}

int	get_map_width(char **map)
{
	int	max_width;
	int	len;
	int	i;

	max_width = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

static int	loop_map(t_data *data, int row, int col)
{
	if (data->map[row][col] == 'N' || data->map[row][col] == 'S'
			|| data->map[row][col] == 'E' || data->map[row][col] == 'W')
	{
		data->player.x = col + 0.5;
		data->player.y = row + 0.5;
		if (data->map[row][col] == 'N')
		{
			data->player.dir_x = 0;
			data->player.dir_y = -1;
		}
		else if (data->map[row][col] == 'S')
		{
			data->player.dir_x = 0;
			data->player.dir_y = 1;
		}
		else if (data->map[row][col] == 'E')
		{
			data->player.dir_x = 1;
			data->player.dir_y = 0;
		}
		else if (data->map[row][col] == 'W')
		{
			data->player.dir_x = -1;
			data->player.dir_y = 0;
		}
		return (0);
	}
	return (-1);
}

int	find_player(t_data *data)
{
	int	row;
	int	col;

	row = 0;
	while (data->map[row])
	{
		col = 0;
		while (data->map[row][col])
		{
			if (loop_map(data, row, col) == 0)
			{
				plane_init(data, 0.66);
				data->map[row][col] = '0';
				return (0);
			}
			col++;
		}
		row++;
	}
	return (-1);
}
