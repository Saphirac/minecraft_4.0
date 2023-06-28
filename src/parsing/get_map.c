/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:39:57 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/27 19:38:58 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_line(char const *const line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && (line[i] != ' ' || line[i] != '1' || line[i] != '0'
			|| line[i] != 'N' || line[i] != 'S'
			|| line[i] != 'E' || line[i] != 'W'))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS)
}

int	check_map(char	*map)
{
	
}

int	get_map(t_map_data *map, char *line, int const fd)
{
	char	*tmp;

	while (line)
	{
		if (check_map_line(line))
			return (free(line), perror("Incorrect map.\n"), EXIT_FAILURE);
		if (!map->map[0])
			map->map = ft_strdup(line);
		else
		{
			tmp = map->map;
			map->map = ft_strjoin(map->map, line);
			free (tmp);
		}
		if (!map->map)
			return (free(line), EXIT_FAILURE);
		map->map_size[Y] += 1;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (check_map(map->map))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
