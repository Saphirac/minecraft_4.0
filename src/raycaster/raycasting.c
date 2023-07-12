/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:39:40 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/12 19:14:21 by gle-mini         ###   ########.fr       */
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
			info->img_data->addr[y * width + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img_data->img, 0, 0);
}

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
void	load_image(t_info *info, int *texture, char *path, t_img_data *img_data)
{
	int y;
	int	x;

	img_data->img = mlx_xpm_file_to_image(info->mlx, path, &img_data->img_width, &img_data->img_height);
	if (!img_data->img)
		//RETURNOUER MLX_ERR
	img_data->addr = mlx_get_data_addr(img_data->img, &img_data->bpp, &img_data->size_l, &img_data->endian);
	y = 0;
	while (y < img_data->img_height)
	{
		x = 0;
		while (x < img_data->img_width)
		{
			printf("x: %d | y: %d\n", x, y);
			texture[img_data->img_width * y + x] = 25;
			//texture[img_data->img_width * y + x] = img_data->addr[img_data->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img_data->img);
}

/**
 * @brief Load textures from the .xmp with load_image function
 *
 * @param
 * @return
 * @throws
 */
void	load_texture(t_info *info, t_map_data *map)
{
	t_img_data	img_data;
	(void)map;

	//Changer le parser
	load_image(info, info->texture[0], "textures/diamond.xpm", &img_data);
	load_image(info, info->texture[1], "textures/mchassig.xpm", &img_data);
	load_image(info, info->texture[2], "textures/wood.xpm", &img_data);
	load_image(info, info->texture[3], "textures/stone.xpm", &img_data);

	/*
	load_image(info, info->texture[0], map->textures_colours[NO], &img);
	load_image(info, info->texture[1], map->textures_colours[SO], &img);
	load_image(info, info->texture[2], map->textures_colours[EA], &img);
	load_image(info, info->texture[3], map->textures_colours[WE], &img);
	*/
}

/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
int	initialize_textures(t_info *info, t_map_data *map)
{
	int	i;
//	int	j;

	if (!(info->texture = (int **)malloc(sizeof(int *) * 4)))
		return (-1);
	i = 0;
	while (i < 4)
	{
		if (!(info->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
		i++;
	}
/*
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < texHeight * texWidth)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	*/
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < )
	{
		x = 0;
		while (x < img_data->img_width)
		{
			printf("x: %d | y: %d\n", x, y);
			texture[img_data->img_width * y + x] = 25;
			//texture[img_data->img_width * y + x] = img_data->addr[img_data->img_width * y + x];
			x++;
		}
		y++;
	}
	load_texture(info, map);
	return (1);
}

int	malloc_buf(int ***buf)
{
	int	i;

	*buf = malloc(sizeof(int *) * height);
	if (!*buf)
		return (MALLOC_ERR);
	i = 0;
	while (i < height)
	{
		(*buf)[i] = malloc(sizeof(int) * width);
		if (!(*buf)[i])
			return (MALLOC_ERR);
		i++;
	}
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

	if (malloc_buf(&info->buf))
		return (MALLOC_ERR);
	info->mlx = NULL;
	info->mlx = mlx_init();
	if (info->mlx == NULL)
		return (MLX_ERR);
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
	if (initialize_textures(info, map_data) == -1)
		return (-1);
	return (1);
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
	draw(info);
	return (0);
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
	t_info info;

	ft_bzero(&info, sizeof(t_info));
	initialize_info_structure(&info, map_data);

	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	if (info.win == NULL || info.mlx == NULL)
		printf("MEYRYRYRM");
	info.img_data->img = mlx_new_image(info.mlx, width, height);
	info.img_data->addr = mlx_get_data_addr(info.img_data->img, &info.img_data->bpp, &info.img_data->size_l, &info.img_data->endian);

	mlx_loop_hook(info.mlx, &raycaster_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, 17, 0L, &handle_cross, &info);

	mlx_loop(info.mlx);
	return (0);
}

