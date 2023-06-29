/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:39:57 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/29 15:11:07 by mcourtoi         ###   ########.fr       */
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

char	**ft_list_to_array_str(int fd, char const *const line)
{
	char	**array;
	t_list	list;
	int		i;

	i = 0;
	ft_bzero(&list, sizeof(t_list));
	if (read_map(&list, line, fd))
		return (EXIT_FAILURE);
	array = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (array == NULL)
		return (NULL);
	while (list)
	{
		array[i] = ft_strdup((char *)list->str);
		if (array[i] == NULL)
			return (NULL);
		list = list->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

inline static char	**alloc_copy_map(char **map)
{
	char	**new_map;
	int		max_x;
	int		max_y;
	int	i;

	max_x = find_max_x(map);
	max_y = ft_arrstrlen(map);
	new_map = malloc(sizeof(char *) * (max_y + 1));
	if (new_map == NULL)
		return (NULL);
	i =  0;
	while (i < max_y)
	{
		new_map[i] = malloc(sizeof(char) * (max_x));
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

inline static void	fill_with_x(char **map)
{
	int		max_x;
	int		max_y;

	max_x = find_max_x(map);
	max_y = ft_arrstrlen(map);
	x = 0;
	y = 0;
	while (y < max_y)
	{
		while (x < max_x)
		{
			if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != 'P')
				new_map[y][x] = 'X';
			x++;
		}
		x = 0;
		y++;
	}
}

char	**copy_map(int fd, char const *const line)
{
	char	**new_map;
	char	**map;
	int		x;
	int		y;

	map = ft_list_to_array_str(fd, line);
	if (!map)
		return (NULL);
	new_map = alloc_copy_map(map);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '\n')
				new_map[y][x] = '\0';
			else
				new_map[y][x] = map[y][x];
			x++;
		}
		y++;
	}
	print_map(new_map);	
	return (fill_with_x(map), new_map);
}
