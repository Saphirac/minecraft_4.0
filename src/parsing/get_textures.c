/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:37:05 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/29 19:39:20 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/**
 * @brief Get the textures, skip the identifiants at the beginning and then get
 * the path to the texture after also skipping the spaces.
 * 
 * @param map struct containing the final map data after parsing
 * @param line getting parsed
 * @param n enum of the actual identifiant being entered
 * @return EXIT_SUCCESS if everything went correctly
 */
static int	get_textures_colours(
	t_map_data *const map,
	char const *const line,
	t_texture const n)
{
	char const	*ptr;

	if (map->textures[n])
		return (perror("Data already exists.\n"), EXIT_FAILURE);
	ptr = line;
	while (*ptr != ' ')
		ptr++;
	while (*ptr == ' ')
		ptr++;
	if (*ptr)
		map->textures[n] = ft_strndup(ptr, ft_strlen(ptr));
	if (!*ptr || !map->textures[n])
		return (perror("Ft_strndup error.\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

inline static bool	__is_line_empty(char const *const line)
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

inline static t_texture	check_line(char const *const line)
{
	if (__is_line_empty(line) == true)
		return (-3);
	if (!line[0] || !line[1] || !line[2])
		return (-2);
	if (line[0] == 'C' && line[1] == ' ')
		return (C);
	if (line[0] == 'F' && line[1] == ' ')
		return (F);
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (SO);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (NO);
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (WE);
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (EA);
	return (-1);
}
/**
 * @brief Get the textures of the wall and the colours of the floor and ceiling
 * 
 * @param map struct containing the textures tab containing all the others
 * @param fd to the given map file
 * @return EXIT_SUCCESS OR FAILURE
 */
int	get_all_data(
	t_map_data *const map,
	int const fd
)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (EXIT_FAILURE);
	while (line)
	{
		if (check_line(line) > 0)
			if (get_textures_colours(map, line, check_line(line)))
				return (EXIT_FAILURE);
		else if (check_line(line) == -1)
			return (get_map(map, line, fd));
		else if (check_line(line) == -2)
			return (perror("Incorrect given data.\n"), EXIT_FAILURE);
		free(line);
		line = get_next_line;
	}
	free(line);
	return (perror("No map.\n"), EXIT_FAILURE);
}
