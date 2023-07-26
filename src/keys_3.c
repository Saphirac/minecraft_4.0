/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:08:19 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/26 22:08:29 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//move right if no wall in right of you
void	key_d(int key, t_info *info)
{
	if (key == KEY_D)
	{
		if (!info->map_data->map[(int)(info->posX + \
		info->dirY * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirY * info->moveSpeed;
		if (!info->map_data->map[(int)(info->posX)][(int)(info->posX + \
				info->dirY * info->moveSpeed)])
			info->posY -= info->dirX * info->moveSpeed;
	}
}

//move left if no wall in left of you
void	key_a(int key, t_info *info)
{
	if (key == KEY_A)
	{
		if (!info->map_data->map[(int)(info->posX + info->dirY \
			* info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirY * info->moveSpeed;
		if (!info->map_data->map[(int)(info->posX)][(int)(info->posX \
			+ info->dirY * info->moveSpeed)])
			info->posY += info->dirX * info->moveSpeed;
	}
}

//move forwards if no wall in front of you
void	key_w(int key, t_info *info)
{
	if (key == KEY_W)
	{
		if (!info->map_data->map[(int)(info->posX + info->dirX \
			* info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!info->map_data->map[(int)(info->posX)][(int)(info->posY \
			+ info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
}

//move backwards if no wall behind you
void	key_s(int key, t_info *info)
{
	if (key == KEY_S)
	{
		if (info->map_data->map[(int)(info->posX - info->dirX \
			* info->moveSpeed)][(int)(info->posY)] != '0')
			info->posX -= info->dirX * info->moveSpeed;
		if (info->map_data->map[(int)(info->posX)][(int)(info->posY \
			- info->dirY * info->moveSpeed)] != '0')
			info->posY -= info->dirY * info->moveSpeed;
	}
}
