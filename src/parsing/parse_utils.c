/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:24:59 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/29 21:53:21 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_arrstrlen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

int	find_max_x(char **map)
{
	int max_x;
	int	y;

	max_x = 0;
	y = 0;
	while (map[y])
	{
		max_x = max(max_x, ft_strlen(map[y]) - 1);
		y++;
	}
	return (max_x);
}

bool	is_correct_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (true);
	return (false);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
