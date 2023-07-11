/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 23:30:03 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/11 23:30:31 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//move forwards if no wall in front of you
void	key_w(int key, t_info *info)
{
	if (key == KEY_W)
	{
		if (!info->map_data->map[(int)(info->posX + info->dirX * info->moveSpeed)] \
				[(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!info->map_data->map[(int)(info->posX)][(int)(info->posY + info->dirY * \
					info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
}

//move backwards if no wall behind you
void	key_s(int key, t_info *info)
{
	if (key == KEY_S)
	{
		if (!info->map_data->map[(int)(info->posX - info->dirX * info->moveSpeed)] \
				[(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!info->map_data->map[(int)(info->posX)][(int)(info->posY - info->dirY * \
					info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
}

//rotate to the right
//both camera direction and camera plane must be rotated
void	key_d(int key, t_info *info)
{
	double	oldDirX;
	double	oldPlaneX;

	if (key == KEY_D)
	{
		oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * \
					 sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * \
					 cos(-info->rotSpeed);
		oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * \
					   sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * \
					   cos(-info->rotSpeed);
	}
}


//rotate to the left
//both camera direction and camera plane must be rotated
void	key_a(int key, t_info *info)
{
	if (key == KEY_A)
	{
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * \
					 sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * \
					 cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * \
					   sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * \
					   cos(info->rotSpeed);
	}
}

void	key_esc(int key, t_info *info)
{
	(void)info;
	if (key == KEY_ESC)
		exit(0);
}

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
int	key_press(int key, t_info *info)
{
	key_w(key, info);
	key_s(key, info);
	key_d(key, info);
	key_a(key, info);
	key_esc(key, info);	
	return (0);
}
