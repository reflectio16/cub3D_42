/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:27:03 by fmoulin           #+#    #+#             */
/*   Updated: 2026/02/25 15:31:19 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		perror("You can't enter less than 2 arguments (including the program file)");
		exit(EXIT_FAILURE);
	}
	else
	{
		t_data	map;
		int 	i;
		int 	len;
		int		fd;
		char	*line;
		
		i = 0;
		len = 0;
		fd = open(argv[1], O_RDONLY);
		while ((line = get_next_line(fd)))
		{
			len++; 
		}
		close(fd);
		map.map = malloc(sizeof(char*) * (len + 1));
		fd = open(argv[1], O_RDONLY);
		while ((line = get_next_line(fd)))
		{
			map.map[i] = line;
			i++; 
		}
		map.map[len] = NULL;
		map_init(&map);
		map_render(&map);
		mlx_loop(map.mlx_connection);
	}
}