/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:27:03 by fmoulin           #+#    #+#             */
/*   Updated: 2026/02/26 18:20:55 by fmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_alloc(t_map *map, int fd)
{
	char	*line;
	int len;

	len = 0;
	while ((line = get_next_line(fd)))
	{
		len++; 
	}
	map->map = malloc(sizeof(char*) * (len + 1));
}

void	get_map(t_map *map, int fd)
{
	char	*line;
	int	i;
	
	i = 0;
	while ((line = get_next_line(fd)))
	{
		map->map[i] = line;
		i++; 
	}
	map->map[i] = NULL;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		perror("You can't enter less than 2 arguments (including the program file)");
		exit(EXIT_FAILURE);
	}
	else
	{
		t_mlx	mlx;
		t_map	map;
		int		fd;

		cub_init(&mlx, &map);
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror("Error with the file descriptor");
			return (1);
		}
		map_alloc(&map, fd);
		close(fd);
		
		fd = open(argv[1], O_RDONLY);
		get_map(&map,fd);
		close(fd);
		
		player_init(&map);
		map_render(&mlx, &map);
		mlx_loop(mlx.mlx_connection);
	}
}