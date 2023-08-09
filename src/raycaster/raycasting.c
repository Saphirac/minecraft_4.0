/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:39:40 by gle-mini          #+#    #+#             */
/*   Updated: 2023/08/09 15:29:31 by gle-mini         ###   ########.fr       */
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
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			info->img.data[y * WIDTH + x] = info->buf[y][x];
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

int	convert_map(t_map_data *map_data)
{
	int	x;
	int	y;

	map_data->map = malloc(sizeof(int *) * (map_data->map_size[Y] + 1));
	if (!map_data->map)
		return (MALLOC_ERR);
	y = 0;
	while (map_data->map_char[y])
	{
		x = 0;
		map_data->map[y] = malloc(sizeof(int) * map_data->map_size[X]);
		if (!map_data->map[y])
			return (free(map_data->map), MALLOC_ERR);
		while (map_data->map_char[y][x])
		{
			map_data->map[y][x] = map_data->map_char[y][x] - '0';
			x++;
		}
		y++;
	}
	map_data->map[y] = NULL;
	return (EXIT_SUCCESS);
}

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
int	raycaster(t_map_data *map_data)
{
	t_info	*info;

	convert_map(map_data);
	info = ft_calloc(1, sizeof(t_info));
	if (info == NULL)
		return (MALLOC_ERR);
	initialize_info_structure(info, map_data);
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "minecraft4.0");
	info->img.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	info->img.data = (int *)mlx_get_data_addr(info->img.img,
			&info->img.bpp, &info->img.size_l, &info->img.endian);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_key_hook(info->win, &key_press, info);
	mlx_hook(info->win, 17, 0L, &handle_cross, info);
	mlx_loop(info->mlx);
	mlx_destroy_window(info->mlx, info->win);
	mlx_destroy_image(info->mlx, info->img.img);
	mlx_destroy_display(info->mlx);
	free_all(map_data, info);
	return (EXIT_SUCCESS);
}
