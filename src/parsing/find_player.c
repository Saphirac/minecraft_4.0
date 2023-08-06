/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:01:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/08/06 22:45:48 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_player(t_map_data *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->map_size[Y])
	{
		x = -1;
		while (++x < map->map_size[X])
		{
			if (map->map_char[y][x] == 'N' || map->map_char[y][x] == 'S'
				|| map->map_char[y][x] == 'W' || map->map_char[y][x] == 'E')
			{
				if (map->player[X] != -1 || map->player[Y] != -1)
					return (printf("Error : two players.\n"), EXIT_FAILURE);
				map->player[X] = (float)x;
				map->player[Y] = (float)y;
				map->player_orientation = map->map_char[y][x];
				map->map_char[y][x] = '0';
			}
		}
	}
	if (map->player[X] == -1 && map->player[Y] == -1)
		return (printf("Error : no player found.\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
