/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:39:40 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/13 13:56:04 by mcourtoi         ###   ########.fr       */
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
void	draw(t_info *info, t_img_data *img_data)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			img_data->addr[y * width + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, img_data->img, 0, 0);
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
	return (1);
}

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
int	raycaster_loop(t_info *info)
{
	if (calc(info) == MALLOC_ERR)
		return (MALLOC_ERR);
	draw(info, &info->img_data);
	return (EXIT_SUCCESS);
}

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
int	raycaster(t_info *info, t_map_data *map_data)
{
	t_img_data	img_data;
	ft_bzero(info, sizeof(t_info));
	ft_bzero(&img_data, sizeof(t_img_data));
	initialize_info_structure(info, map_data);

	info->win = mlx_new_window(info->mlx, height, width, "cub3d");
	if (!info->win)
		return (free(info->mlx), perror("Mlx error"), EXIT_FAILURE);
	img_data.img = mlx_new_image(info->mlx, width, height);
	if (!img_data.img)
		return (free(info->win), perror("Mlx error"), EXIT_FAILURE);
	img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bpp,
			&img_data.size_l, &img_data.endian);
	if (initialize_textures(info, &img_data, map_data))
		return (EXIT_FAILURE);
	info->img_data = img_data;
	if (raycaster_loop(info))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

