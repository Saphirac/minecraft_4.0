/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:39:57 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/25 20:26:06 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Get the block corresponding to the given pos in the map. If pos is out
 * of the map, gives automatically a wall (1).
 * 
 * @param map contains the char map with all blocks
 * @param pos given position
 * @return which block 
 */
char	get_block(t_map_data *map, t_v2i pos)
{
	if (pos[X] < 0 || pos[Y] < 0
		|| pos[X] >= map->map_size[X] || pos[Y] >= map->map_size[Y])
		return ('1');
	return (map->map[pos[X] + pos[Y] * map->map_size[X]]);
}
