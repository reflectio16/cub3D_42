/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:58:41 by meelma            #+#    #+#             */
/*   Updated: 2026/03/14 15:03:26 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_args(int ac, char *filename)
{
	int	len;

	if (ac != 2)
		return (print_error("Wrong argument count"));
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
		return (print_error("Wrong file extension. Must be .cub"));
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_list	*map_list;

	map_list = NULL;
	ft_memset(&game, 0, sizeof(t_game));
	game.data.colors.floor = -1;
	game.data.colors.ceiling = -1;
	if (check_args(ac, av[1]) == -1)
		return (1);
	if (parse_file(av[1], &game.data, &map_list) == -1)
	{
		free_data(&game.data);
		return (1);
	}
	if (setup_map(&game.data, map_list) == -1)
	{
		free_data(&game.data);
		return (1);
	}
	game.data.tile = 7;
	cub_init(&game, &game.mlx, &game.data);
	cub_render(&game.mlx, &game.data, game.data.tile);
	mlx_loop(game.mlx.connection);
	free_data(&game.data);
	return (0);
}
