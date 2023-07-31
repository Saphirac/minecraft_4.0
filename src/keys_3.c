/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:08:19 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/27 20:39:55 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//move right if no wall in right of you
void	key_d(int key, t_info *info)
{
	if (key == KEY_D)
	{
		if (!info->map_data->map[(int)(info->vec_pos[Y])] \
				[(int)(info->vec_pos[X] + info->vec_dir[Y] * info->move_speed)])
			info->vec_pos[X] += info->vec_dir[Y] * info->move_speed;
		if (!info->map_data->map[(int)(info->vec_pos[Y] - info->vec_dir[X] * \
					info->move_speed)][(int)(info->vec_pos[X])])
			info->vec_pos[Y] -= info->vec_dir[X] * info->move_speed;
	}
}

//move left if no wall in left of you
void	key_a(int key, t_info *info)
{
	if (key == KEY_A)
	{
		if (!info->map_data->map[(int)(info->vec_pos[Y])] \
				[(int)(info->vec_pos[X] - info->vec_dir[Y] * info->move_speed)])
			info->vec_pos[X] -= info->vec_dir[Y] * info->move_speed;
		if (!info->map_data->map[(int)(info->vec_pos[Y] + info->vec_dir[X] * \
			info->move_speed)][(int)(info->vec_pos[X])])
			info->vec_pos[Y] += info->vec_dir[X] * info->move_speed;
	}
}

//move forwards if no wall in front of you
void	key_w(int key, t_info *info)
{
	if (key == KEY_W)
	{
		if (!info->map_data->map[(int)(info->vec_pos[Y])] \
				[(int)(info->vec_pos[X] + info->vec_dir[X] * info->move_speed)])
			info->vec_pos[X] += info->vec_dir[X] * info->move_speed;
		if (!info->map_data->map[(int)(info->vec_pos[Y] + info->vec_dir[Y] * \
			info->move_speed)][(int)(info->vec_pos[X])])
			info->vec_pos[Y] += info->vec_dir[Y] * info->move_speed;
	}
}

//move backwards if no wall behind you
void	key_s(int key, t_info *info)
{
	if (key == KEY_S)
	{
		if (!info->map_data->map[(int)(info->vec_pos[Y])] \
				[(int)(info->vec_pos[X] - info->vec_dir[X] * info->move_speed)])
			info->vec_pos[X] -= info->vec_dir[X] * info->move_speed;
		if (!info->map_data->map[(int)(info->vec_pos[Y] - info->vec_dir[Y] * \
					info->move_speed)][(int)(info->vec_pos[X])])
			info->vec_pos[Y] -= info->vec_dir[Y] * info->move_speed;
	}
}
