/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:39:40 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/14 08:48:50 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief copy all color stored in info->buf into info->img.data 
 * and print it on the window with mlx_put_image_to_window
 *
 * @param t_info *info: the info data structure
 * @return void
 * @throws
 */
void	draw(t_info *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			info->img.data[y * width + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
int	calc(t_info *info)
{
	if (floor_casting(info) == MALLOC_ERR)
		return (MALLOC_ERR);
	if (wall_casting(info) == MALLOC_ERR)
		return (MALLOC_ERR);
	return (EXIT_SUCCESS);
}

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
int	main_loop(t_info *info)
{
	if (calc(info) == MALLOC_ERR)
		return (MALLOC_ERR);
	draw(info);
	return (0);
}

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

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

/**
 * @brief Load textures from the .xmp with load_image function
 *
 * @param
 * @return
 * @throws
 */
void	load_texture(t_info *info)
{
	t_img	img;

	//load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	//load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[0], "textures/diamond.xpm", &img);
	load_image(info, info->texture[1], "textures/stone_minecraft.xpm", &img);
	load_image(info, info->texture[2], "textures/stone_minecraft.xpm", &img);
	load_image(info, info->texture[3], "textures/stone_minecraft.xpm", &img);
	load_image(info, info->texture[4], "textures/stone_minecraft.xpm", &img);
	load_image(info, info->texture[5], "textures/stone_minecraft.xpm", &img);
	load_image(info, info->texture[6], "textures/stone_minecraft.xpm", &img);
	load_image(info, info->texture[7], "textures/stone_minecraft.xpm", &img);
}

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
int	initialize_textures(t_info *info)
{
	int	i;
	int	j;

	if (!(info->texture = (int **)malloc(sizeof(int *) * 8)))
		return (-1);
	i = 0;
	while (i < 8)
	{
		if (!(info->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < texHeight * texWidth)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	load_texture(info);
	return (EXIT_SUCCESS);
}

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
int	initialize_info_structure(t_info *info, t_map_data *map_data)
{
	int	i;
	int	j;

	info->mlx = mlx_init();
	info->posX = 22.0;
	info->posY = 11.5;
	info->dirX = -1.0;
	info->dirY = 0.0;
	info->planeX = 0.0;
	info->planeY = 0.66;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
	info->map_data = map_data;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			info->buf[i][j] = 0;
			j++;
		}
		i++;
	}
	if (initialize_textures(info) == -1)
		return (-1);
	return (EXIT_SUCCESS);
}

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
int		raycaster(t_map_data *map_data)
{
	t_info info;
	initialize_info_structure(&info, map_data);


	
	info.win = mlx_new_window(info.mlx, width, height, "minecraft4.0");

	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);

	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);

	mlx_loop(info.mlx);
	return (EXIT_SUCCESS);
}

