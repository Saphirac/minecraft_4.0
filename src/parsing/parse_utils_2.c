/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:10:34 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/27 20:11:00 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_map_data *map)
{
	int	y;

	y = 0;
	while (map->textures_colours[y])
	{
		printf("%s\n", map->textures_colours[y]);
		y++;
	}
	y = 0;
	while (map->map_char[y])
	{
		printf("%s\n", map->map_char[y]);
		y++;
	}
}

void	print_only_map(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		printf("%s\n", map[y]);
		y++;
	}
}

bool	is_line_empty(char const *const line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}
