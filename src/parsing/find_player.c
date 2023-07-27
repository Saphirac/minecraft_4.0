/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:01:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/25 18:11:41 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_player(t_map_data *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->map_size[Y])
	{
		x = 0;
		while (x < map->map_size[X])
		{
			if (map->map_char[y][x] == 'N' || map->map_char[y][x] == 'S'
				|| map->map_char[y][x] == 'W' || map->map_char[y][x] == 'E')
			{
				map->player[X] = (float)x;
				map->player[Y] = (float)y;
				map->player_orientation = map->map_char[y][x];
				map->map_char[y][x] = '0';
				return (EXIT_SUCCESS);
			}
			x++;
		}
		y++;
	}
	return (printf("No player found.\n"), EXIT_FAILURE);
}
