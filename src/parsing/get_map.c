/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:39:57 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/29 21:55:09 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_map(t_list *map_list, char const *const line, int fd)
{
	while (line)
	{
		if (ft_lstadd_back(map_list, line))
			return (EXIT_FAILURE)
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (EXIT_SUCCESS);
}

static int	ft_list_to_array_str(char ***array, int fd, char const *const line)
{
	t_list	list;
	int		i;

	i = 0;
	ft_bzero(&list, sizeof(t_list));
	if (read_map(&list, line, fd))
		return (EXIT_FAILURE);
	*array = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (!*array)
		return (EXIT_FAILURE);
	while (list)
	{
		*array[i] = ft_strdup((char *)list->str);
		if (!*array[i])
			return (EXIT_FAILURE);
		list = list->next;
		i++;
	}
	*array[i] = NULL;
	ft_lstclear(&list);
	return (EXIT_SUCCESS);
}

inline static int	alloc_copy_map(t_map_data *map, char **map)
{
	int	i;

	map->map_size[X] = find_max_x(map);
	map->map_size[Y] = ft_arrstrlen(map);
	map->map = malloc(sizeof(char *) * (map->map_size[Y] + 1));
	if (!map->map)
		return (EXIT_FAILURE);
	i =  0;
	while (i < map->map_size[Y])
	{
		map->map[i] = malloc(sizeof(char) * (map->map_size[X]));
		if (!map->map[i])
			return (EXIT_FAILURE);
		i++;
	}
	map->map[i] = NULL;
	return (EXIT_SUCCESS);
}

inline static void	fill_with_x(t_map_data *map)
{
	x = 0;
	y = 0;
	while (y < map->map_size[Y])
	{
		while (x < map->map_size[X])
		{
			if (is_correct_char(map->map[y][x]) == false)
				map->map[y][x] = 'X';
			x++;
		}
		x = 0;
		y++;
	}
}

int	get_map(t_map_data *map, fd, char const *const line)
{
	char	**map_tmp;
	int		x;
	int		y;

	if (ft_list_to_array_str(map_tmp, fd, line)
		|| alloc_copy_map(map, map_tmp))
		return (EXIT_FAILURE);
	y = 0;
	while (map_tmp[y])
	{
		x = 0;
		while (map_tmp[y][x])
		{
			if (map_tmp[y][x] == '\n')
				map->map[y][x] = '\0';
			else
				map->map[y][x] = map[y][x];
			x++;
		}
		y++;
	}
	ft_free(map_tmp);
	print_map(map->map);
	fill_with_x(map->map);
	return (EXIT_SUCCESS);
}
