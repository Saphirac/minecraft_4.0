/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:09:47 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/27 20:38:21 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//rotate to the right
//both camera direction and camera plane must be rotated
void	key_right(int key, t_info *info)
{
	double	olddirx;
	double	oldplanex;

	if (key == KEY_RIGHT)
	{
		olddirx = info->vec_dir[X];
		info->vec_dir[X] = info->vec_dir[X] * cos(-info->rot_speed) - info->vec_dir[Y] * \
					sin(-info->rot_speed);
		info->vec_dir[Y] = olddirx * sin(-info->rot_speed) + info->vec_dir[Y] * \
					cos(-info->rot_speed);
		oldplanex = info->plane_x;
		info->plane_x = info->plane_x * cos(-info->rot_speed) - info->plane_y * \
					sin(-info->rot_speed);
		info->plane_y = oldplanex * sin(-info->rot_speed) + info->plane_y * \
					cos(-info->rot_speed);
	}
}

//rotate to the left
//both camera direction and camera plane must be rotated
void	key_left(int key, t_info *info)
{
	double	olddirx;
	double	oldplanex;

	if (key == KEY_LEFT)
	{
		olddirx = info->vec_dir[X];
		info->vec_dir[X] = info->vec_dir[X] * cos(info->rot_speed) - info->vec_dir[Y] * \
					sin(info->rot_speed);
		info->vec_dir[Y] = olddirx * sin(info->rot_speed) + info->vec_dir[Y] * \
					cos(info->rot_speed);
		oldplanex = info->plane_x;
		info->plane_x = info->plane_x * cos(info->rot_speed) - info->plane_y * \
					sin(info->rot_speed);
		info->plane_y = oldplanex * sin(info->rot_speed) + info->plane_y * \
					cos(info->rot_speed);
	}
}

/**
 * @brief
 *
 * @param
 * @return
 * @throwns
 */
int	key_press(int key, t_info *info)
{
	key_w(key, info);
	key_s(key, info);
	key_a(key, info);
	key_d(key, info);
	key_right(key, info);
	key_left(key, info);
	key_esc(key, info);
	return (0);
}
