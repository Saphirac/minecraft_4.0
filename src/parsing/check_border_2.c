/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:09:15 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/27 20:09:28 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**create_map_tmp(t_map_data *src)
{
	char	**tmp;
	int		x;
	int		y;

	tmp = malloc(sizeof(char *) * (src->map_size[Y] + 1));
	if (!tmp)
		return (NULL);
	y = 0;
	while (y < src->map_size[Y])
	{
		x = 0;
		tmp[y] = malloc(sizeof(char) * (src->map_size[X] + 1));
		if (!tmp[y])
			return (NULL);
		while (x < src->map_size[X])
		{
			tmp[y][x] = src->map_char[y][x];
			x++;
		}
		tmp[y][x] = '\0';
		y++;
	}
	tmp[y] = 0;
	return (tmp);
}
