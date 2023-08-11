/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:53:37 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/08/11 11:27:56 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_map(t_map_data *map, char *file)
{
	int	fd;

	ft_bzero(map, sizeof(t_map_data));
	fd = open_file(file);
	if (fd < 0)
		return (printf("Error : can't open map.\n"), EXIT_FAILURE);
	if (get_all_data(map, fd) || check_border(map) == false)
		return (close(fd), EXIT_FAILURE);
	if (close(fd) == -1)
		return (EXIT_FAILURE);
	return (close(fd), EXIT_SUCCESS);
}

// TODO : Open and check args
int	main(int ac, char **av)
{
	t_map_data	map;

	if (ac != 2)
		return (printf("Error : incorrect number of arguments.\n"), 1);
	if (create_map(&map, av[1]))
		return (1);
	if (get_color_ceiling_floor(&map) == EXIT_FAILURE)
		return (ft_free(map.map_char), free_textures(map.textures_colours),
			EXIT_FAILURE);
	raycaster(&map);
	return (0);
}
