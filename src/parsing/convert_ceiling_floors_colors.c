/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ceiling_floors_colors.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:00:02 by gle-mini          #+#    #+#             */
/*   Updated: 2023/08/11 12:38:20 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_correct_char_colour(char *str)
{
	while (*str)
	{
		if ((*str < '0' || *str > '9') && *str != ',')
			return (printf("Error : incorrect colour for ceiling or floor.\n"),
				false);
		str++;
	}
	return (true);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	convert_colors(char *str)
{
	char	**s;
	int		color;

	if (is_correct_char_colour(str) == false)
		return (EXIT_FAILURE);
	s = ft_split(str, ",");
	if (ft_arrstrlen(s) != 3)
		return (free(s),
			printf("Error : incorrect colour of ceiling or floor.\n"),
			EXIT_FAILURE);
	color = create_trgb(1, ft_atoi(s[0]), ft_atoi(s[1]), ft_atoi(s[2]));
	free(s);
	s = NULL;
	return (color);
}

int	get_color_ceiling_floor(t_map_data *map_data)
{
	int	color_floor;
	int	color_ceiling;

	color_floor = convert_colors(map_data->textures_colours[4]);
	if (color_floor == EXIT_FAILURE)
		return (EXIT_FAILURE);
	color_ceiling = convert_colors(map_data->textures_colours[5]);
	if (color_ceiling == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map_data->color_floor = color_floor;
	map_data->color_ceiling = color_ceiling;
	return (EXIT_SUCCESS);
}
