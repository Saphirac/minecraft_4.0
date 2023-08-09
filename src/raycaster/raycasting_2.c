/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:05:01 by gle-mini          #+#    #+#             */
/*   Updated: 2023/08/09 16:41:24 by gle-mini         ###   ########.fr       */
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
void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(info->mlx, path,
			&img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->size_l, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
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

	load_image(info, info->texture[0],
		info->map_data->textures_colours[0], &img);
	load_image(info, info->texture[1],
		info->map_data->textures_colours[1], &img);
	load_image(info, info->texture[2],
		info->map_data->textures_colours[2], &img);
	load_image(info, info->texture[3],
		info->map_data->textures_colours[3], &img);
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

	info->texture = malloc(sizeof(int *) * 4);
	if (!(info->texture))
		return (MALLOC_ERR);
	i = 0;
	while (i < 4)
	{
		info->texture[i] = ft_calloc((TEXHEIGHT * TEXWIDTH), sizeof(int));
		if (!(info->texture[i]))
			return (MALLOC_ERR);
		i++;
	}
	load_texture(info);
	return (EXIT_SUCCESS);
}

int	sub_initialize_info(t_info *info, t_map_data *map_data)
{
	info->vec_pos[X] = map_data->player[X];
	info->vec_pos[Y] = map_data->player[Y];
	initialize_orientation(info, map_data);
	info->move_speed = 0.15;
	info->rot_speed = 0.15;
	info->map_data = map_data;
	info->wc_data = malloc(sizeof(t_wc_data) * 1);
	if (info->wc_data == NULL)
		return (MALLOC_ERR);
	info->fc_data = malloc(sizeof(t_fc_data) * 1);
	if (info->fc_data == NULL)
		return (free(info->wc_data), free(info->mlx), MALLOC_ERR);
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
	if (info->mlx == NULL)
		return (MLX_ERR);
	if (sub_initialize_info(info, map_data))
		return (EXIT_FAILURE);
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
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
