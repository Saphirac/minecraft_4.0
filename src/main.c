/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:53:37 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/20 12:50:36 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_map(t_map_data *map, char *file)
{
	int	fd;

	ft_bzero(map, sizeof(t_map_data));

	fd = open_file(file);
	if (fd < 0)
		return (EXIT_FAILURE);
	if (get_all_data(map, fd) || check_border(map) == false)
		return (EXIT_FAILURE);
	if (close(fd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// TODO : Open and check args
int	main(int ac, char **av)
{
	t_map_data	map;

	if (ac != 2)
		return (1);
	if (create_map(&map, av[1]))
		return (1);
	if (get_color_ceiling_floor(&map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	raycaster(&map);
	return (0);
}
