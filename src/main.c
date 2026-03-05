/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoulin <fmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:27:03 by fmoulin           #+#    #+#             */
/*   Updated: 2026/03/05 14:58:24 by fmoulin          ###   ########.fr       */
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
		t_mlx	mlx;
		t_map	map;
		int		fd;
		int		tile;

		tile = 5;
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
		cub_render(&mlx, &map, tile);
		mlx_loop(mlx.mlx_connection);
	}
}