/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:09:47 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/20 13:03:51 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//move right if no wall in right of you
void	key_d(int key, t_info *info)
{
	if (key == KEY_D)
	{
		if (!info->map_data->map[(int)(info->posY)] \
				[(int)(info->posX + info->dirY * info->moveSpeed)])
			info->posX += info->dirY * info->moveSpeed;
		if (!info->map_data->map[(int)(info->posY - info->dirX * \
					info->moveSpeed)][(int)(info->posX)])
			info->posY -= info->dirX * info->moveSpeed;
	}
}
//move left if no wall in left of you
void	key_a(int key, t_info *info)
{
	if (key == KEY_A)
	{
		if (!info->map_data->map[(int)(info->posY)] \
				[(int)(info->posX - info->dirY * info->moveSpeed)])
			info->posX -= info->dirY * info->moveSpeed;
		if (!info->map_data->map[(int)(info->posY + info->dirX * info->moveSpeed)] \
				[(int)(info->posX)])
			info->posY += info->dirX * info->moveSpeed;
	}
}

//move forwards if no wall in front of you
void	key_w(int key, t_info *info)
{
	if (key == KEY_W)
	{
		if (!info->map_data->map[(int)(info->posY)] \
				[(int)(info->posX + info->dirX * info->moveSpeed)])
			info->posX += info->dirX * info->moveSpeed;
		if (!info->map_data->map[(int)(info->posY + info->dirY * info->moveSpeed)] \
				[(int)(info->posX)])
			info->posY += info->dirY * info->moveSpeed;
		//printf("after info->posY: %f | info->posX: %f\n", info->posY, info->posX);
	}
}

//move backwards if no wall behind you
void	key_s(int key, t_info *info)
{
	if (key == KEY_S)
	{
		if (!info->map_data->map[(int)(info->posY)] \
				[(int)(info->posX - info->dirX * info->moveSpeed)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!info->map_data->map[(int)(info->posY - info->dirY * \
					info->moveSpeed)][(int)(info->posX)])
			info->posY -= info->dirY * info->moveSpeed;
	}
}

//rotate to the right
//both camera direction and camera plane must be rotated
void	key_right(int key, t_info *info)
{
	double	oldDirX;
	double	oldPlaneX;

	if (key == KEY_RIGHT)
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
void	key_left(int key, t_info *info)
{
	double	oldDirX;
	double	oldPlaneX;

	if (key == KEY_LEFT)
	{
		oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * \
					 sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * \
					 cos(info->rotSpeed);
		oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * \
					   sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * \
					   cos(info->rotSpeed);
	}
}

void	key_esc(int key, t_info *info)
{
	if (key == KEY_ESC)
		mlx_loop_end(info->mlx);
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
