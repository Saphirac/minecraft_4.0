/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:39:57 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/08/09 14:29:49 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline static bool	__is_map_line_correct(char const *const line)
{
	size_t	i;

	if (is_line_empty(line) == true)
		return (false);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n'
			&& is_correct_char(line[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

int	read_map(t_str_lst *map_list, char *line, int fd)
{
	while (line && __is_map_line_correct(line) == true)
	{
		if (!str_lst_add_back(map_list, line))
			return (printf("Error : str_lst creation.\n"), free(line), EXIT_FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (EXIT_SUCCESS);
}

inline static void	copy_or_fill_with_x(t_str_lst *list,
										char *src,
										char *map_line)
{
	size_t	i;

	i = 0;
	while (i < list->max_line_size - 1)
	{
		if (is_correct_char(src[i]) == true)
			map_line[i] = src[i];
		else
			map_line[i] = 'X';
		i++;
	}
	map_line[i] = '\0';
}

static int	ft_list_to_array_str(t_map_data *map, t_str_lst *list)
{
	t_str		*iter;
	size_t		i;

	iter = list->head;
	i = 0;
	while (iter)
	{
		map->map_char[i] = malloc(sizeof(char) * (list->max_line_size));
		if (!map->map_char[i])
			return (printf("Error : malloc failed.\n"), EXIT_FAILURE);
		copy_or_fill_with_x(list, iter->str, map->map_char[i]);
		i++;
		iter = iter->next;
	}
	map->map_char[i] = 0;
	return (EXIT_SUCCESS);
}

int	get_map(t_map_data *map, int fd, char *line)
{
	t_str_lst	list;

	if (is_textures_full(map) == false)
		return (printf("Error : didn't get all data.\n"), free(line), EXIT_FAILURE);
	ft_bzero(&list, sizeof(t_str_lst));
	if (read_map(&list, line, fd))
		return (printf("Error : incorrect map.\n"), free_textures(map->textures_colours), EXIT_FAILURE);
	map->map_size[X] = list.max_line_size - 1;
	map->map_size[Y] = list.size;
	map->map_char = malloc(sizeof(char *) * (list.size + 1));
	if (!map->map_char)
		return (printf("Error : malloc failed.\n"), free_textures(map->textures_colours), EXIT_FAILURE);
	if (ft_list_to_array_str(map, &list))
		return (EXIT_FAILURE);
	str_lst_clear(&list);
	map->player[X] = -1;
	map->player[Y] = -1;
	if (find_player(map))
		return (free_textures(map->textures_colours), ft_free(map->map_char), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
