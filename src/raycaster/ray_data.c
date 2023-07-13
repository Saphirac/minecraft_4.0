/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:33:28 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/12 21:29:57 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/**
 * @brief
 *
 * @param
 * @return
 * @throws
 */
int	load_image(t_info *info, int *texture, char *path, t_img_data *img_data)
{
	int y;
	int	x;

	img_data->img = mlx_xpm_file_to_image(info->mlx, path, &img_data->img_width, &img_data->img_height);
	if (!img_data->img)
		return (EXIT_FAILURE);
	img_data->addr = mlx_get_data_addr(img_data->img, &img_data->bpp, &img_data->size_l, &img_data->endian);
	y = 0;
	while (y < img_data->img_height)
	{
		x = 0;
		while (x < img_data->img_width)
		{
			//printf("x: %d | y: %d\n", x, y);
			texture[img_data->img_width * y + x] = 25;
			//texture[img_data->img_width * y + x] = img_data->addr[img_data->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img_data->img);
	return (EXIT_SUCCESS);
}

/**
 * @brief Load textures from the .xmp with load_image function
 *
 * @param
 * @return
 * @throws
 */
void	load_texture(t_info *info, t_img_data *img_data, t_map_data *map)
{
	(void)map;

	//TODO Changer le parser
	load_image(info, info->texture[0], "textures/diamond.xpm", img_data);
	load_image(info, info->texture[1], "textures/mchassig.xpm", img_data);
	load_image(info, info->texture[2], "textures/wood.xpm", img_data);
	load_image(info, info->texture[3], "textures/stone.xpm", img_data);

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
int	initialize_textures(t_info *info, t_img_data *img_data, t_map_data *map)
{
	int	i;

	if (!(info->texture = malloc(sizeof(int *) * 4)))
		return (EXIT_FAILURE);
	i = 0;
	while (i < 4)
	{
		if (!(info->texture[i] = ft_calloc((texHeight * texWidth), sizeof(int))))
			return (EXIT_FAILURE);
		i++;
	}
	load_texture(info, img_data, map);
	return (EXIT_SUCCESS);
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
		(*buf)[i] = ft_calloc(width, sizeof(int));
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
int	initialize_info_structure(
	t_info *info,
	t_map_data *map_data)
{
	if (malloc_buf(&info->buf))
		return (MALLOC_ERR);
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
	return (EXIT_SUCCESS);
}
