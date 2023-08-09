/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_orientation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:26:21 by gle-mini          #+#    #+#             */
/*   Updated: 2023/08/09 16:45:27 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	east_orientation(t_info *info)
{
	info->vec_dir[X] = -1.0;
	info->vec_dir[Y] = 0;
	info->vec_plane[X] = 0.00;
	info->vec_plane[Y] = 0.66;
}

void	west_orientation(t_info *info)
{
	info->vec_dir[X] = 1.0;
	info->vec_dir[Y] = 0;
	info->vec_plane[X] = 0.00;
	info->vec_plane[Y] = -0.66;
}

void	south_orientation(t_info *info)
{
	info->vec_dir[X] = 0;
	info->vec_dir[Y] = 1.0;
	info->vec_plane[X] = 0.66;
	info->vec_plane[Y] = 0.00;
}

void	north_orientation(t_info *info)
{
	info->vec_dir[X] = 0;
	info->vec_dir[Y] = -1.0;
	info->vec_plane[X] = -0.66;
	info->vec_plane[Y] = 0.00;
}

void	initialize_orientation(t_info *info, t_map_data *map_data)
{
	if (map_data->player_orientation == 'E')
		east_orientation(info);
	else if (map_data->player_orientation == 'W')
		west_orientation(info);
	else if (map_data->player_orientation == 'S')
		south_orientation(info);
	else if (map_data->player_orientation == 'N')
		north_orientation(info);
}
