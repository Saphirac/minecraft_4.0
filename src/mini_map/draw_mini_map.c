/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:05:10 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/08/02 16:05:10 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline static void	__draw_mini_map_line(t_img img, t_map_data *map, t_v2i i)
{
	t_v2i const	offset = {20, 20};

	if (get_block(map, i) != '1' && get_block(map, i) != 'X')
	{
		if (get_block(map, i + (t_v2i){-1, 0}) == '1')
			draw_line(img, offset + i * MINI_MAP_SIZE,
				offset + (i + (t_v2i){0, 1}) * MINI_MAP_SIZE, 0xFFFFFF);
		if (get_block(map, i + (t_v2i){1, 0}) == '1')
			draw_line(img, offset + (i + (t_v2i){1, 0}) * MINI_MAP_SIZE,
				offset + (i + (t_v2i){1, 1}) * MINI_MAP_SIZE, 0xFFFFFF);
		if (get_block(map, i + (t_v2i){0, -1}) == '1')
			draw_line(img, offset + i * MINI_MAP_SIZE,
				offset + (i + (t_v2i){1, 0}) * MINI_MAP_SIZE, 0xFFFFFF);
		if (get_block(map, i + (t_v2i){0, 1}) == '1')
			draw_line(img, offset + (i + (t_v2i){0, 1}) * MINI_MAP_SIZE,
				offset + (i + (t_v2i){1, 1}) * MINI_MAP_SIZE, 0xFFFFFF);
	}
}

void	draw_mini_map(t_img img, t_map_data *map)
{
	t_v2i	i;

	i[X] = 0;
	while (i[X] < map->map_size[X])
	{
		i[Y] = 0;
		while (i[Y] < map->map_size[Y])
		{
			__draw_mini_map_line(img, map, i);
			i[Y]++;
		}
		i[X]++;
	}
}
