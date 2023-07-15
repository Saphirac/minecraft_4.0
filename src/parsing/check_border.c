/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:57:37 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/11 13:32:13 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the coordinates (x,y) are borders
 *
 * @param char **map: the map
 * @param int x: the coordinate x 
 * @param int y: the coordinate y 
 * @return boolean 1 if is border, 0 if isn't
 * @throws
*/
inline static int	__is_border(t_map_data *map, int x, int y)
{
	if (x == 0 || y == 0 || x == map->map_size[X] \
			|| y == map->map_size[Y])
		return (1);
	return (0);
}

/**
 * @brief Check if the case is a traversable 
 *
 * @param char **map: the map
 * @param int x: the coordinate x 
 * @param int y: the coordinate y  
 * @return boolean 1 if the case is traversable, 0 if isn't
 * @throws
*/
inline static int	__is_valid(char **map, int x, int y)
{
	if (map[y][x] == '0')
		return (1);
	return (0);
}

/**
 * @brief Change character to mark backtracking algorithm passage
 *
 * @param char *original: the original map character
 * @param char *tmp_char: the temporary char to mark the backtraking 
 * algorithm passage
 * @return void
 * @throws
*/
inline static void	__fill_map(char *original, char *tmp_char)
{
	*tmp_char = *original;
	if (*original == '0')
		*original = '2';
	else
		*original = '3';
}

/**
 * @brief Backtracking algorithm wich croses and marks the passage in 
 * order to check if the map is well closed by walls
 *
 * The algorithm start at the players coordinates
 *
 * @param char **map: the map you want to check
 * @param int x, int y: the (x, y) player coordinates
 * @return boolean 1 if isn't closed, 0 if it is
 * @throws
*/
static int	ft_find_border(t_map_data *map, char **map_tmp, int x, int y)
{
	char	tmp_char;

	if ((__is_border(map, x, y) == 1) && map_tmp[y][x] == '0')
		return (1);
	if (x < 0 || x == map->map_size[X]
		|| y < 0 || y == map->map_size[Y])
		return (0);
	if (__is_valid(map_tmp, x, y))
	{
		__fill_map(&(map_tmp[y][x]), &tmp_char);
		if (ft_find_border(map, map_tmp, x + 1, y)
			|| ft_find_border(map, map_tmp, x - 1, y)
			|| ft_find_border(map, map_tmp, x, y + 1)
			|| ft_find_border(map, map_tmp, x, y - 1))
			return (1);
	}
	return (0);
}

char	**create_map_tmp(t_map_data *src)
{
	char	**tmp;
	int		x;
	int		y;

	tmp = malloc(sizeof(char *) * src->map_size[Y]);
	if (!tmp)
		return (NULL);
	y = 0;
	while (y < src->map_size[Y])
	{
		x = 0;
		tmp[y] = malloc(sizeof(char) * src->map_size[X]);
		if (!tmp[y])
			return (NULL);
		while (x < src->map_size[X])
		{
			tmp[y][x] = src->map[y][x];
			x++;
		}
		y++;
	}
	print_only_map(tmp);
	return (tmp);
}

/**
 * @brief Function that use copy_map to transforme the map into
 * a rectangle malloc map in order to simplify 
 * the backtracking walls checking 
 *
 * @param char **map: the map you want to check
 * @return 1 if the map is closed by walls else 0 if isnt
 * @throws Print on the STDOUT "Map is not closed by wall" if it is
 * @throws Return MALLOC_ERR is there is malloc error
*/
bool	check_border(t_map_data *map)
{
	char	**tmp;

	tmp = create_map_tmp(map);
	if (!tmp)
		return (false);
	if (ft_find_border(map, tmp, (int)map->player[X], (int)map->player[Y]) == 1)
	{
		printf("Map is not closed by wall\n");
		ft_free(tmp);
		return (false);
	}
	ft_free(tmp);
	return (true);
}
