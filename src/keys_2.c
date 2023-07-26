/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:09:47 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/26 22:08:06 by mcourtoi         ###   ########.fr       */
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
		olddirx = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * \
					sin(-info->rotSpeed);
		info->dirY = olddirx * sin(-info->rotSpeed) + info->dirY * \
					cos(-info->rotSpeed);
		oldplanex = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * \
					sin(-info->rotSpeed);
		info->planeY = oldplanex * sin(-info->rotSpeed) + info->planeY * \
					cos(-info->rotSpeed);
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
		olddirx = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * \
					sin(info->rotSpeed);
		info->dirY = olddirx * sin(info->rotSpeed) + info->dirY * \
					cos(info->rotSpeed);
		oldplanex = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * \
					sin(info->rotSpeed);
		info->planeY = oldplanex * sin(info->rotSpeed) + info->planeY * \
					cos(info->rotSpeed);
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
