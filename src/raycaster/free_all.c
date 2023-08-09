/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:01:15 by gle-mini          #+#    #+#             */
/*   Updated: 2023/08/09 15:45:47 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(char **str)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		free(str[i]);
		i++;
	}
}

void	ft_free_int_tab(int **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_int(int **tab)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_int_tab(int **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_all(t_map_data *map_data, t_info *info)
{
	free(info->mlx);
	free_textures(map_data->textures_colours);
	ft_free(map_data->map_char);
	ft_free_int_tab(map_data->map);
	free_int(info->texture);
	free(info->wc_data);
	free(info->fc_data);
	free(info);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}
