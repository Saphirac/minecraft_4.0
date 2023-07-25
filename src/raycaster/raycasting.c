/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:39:40 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/25 18:27:59 by mcourtoi         ###   ########.fr       */
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
void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int x;
	int y;

	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
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

	load_image(info, info->texture[0], info->map_data->textures_colours[0], &img);
	load_image(info, info->texture[1], info->map_data->textures_colours[1], &img);
	load_image(info, info->texture[2], info->map_data->textures_colours[2], &img);
	load_image(info, info->texture[3], info->map_data->textures_colours[3], &img);
}

void print_map_char(t_info *info)
{
	int	x;
	int	y;
	t_map_data *map_data;

	map_data = info->map_data;
	y = 0;
	while (y < map_data->map_size[Y])
	{
		x = 0;
		while (x < map_data->map_size[X])
		{
			printf("%d", map_data->map_char[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

/**
 * @brief debug function, print all textures
 *
 * @param
 * @return
 * @throws
 */
void	print_textures(t_info *info)
{
	int i;
	int	x;
	int	y;

	i = 0;
	while (i < 4)
	{
		y = 0;
		while (y < texHeight)
		{
			x = 0;
			while (x < texWidth)
			{
				printf("%d", info->texture[i][y + x]);	
				x++;
			}
			printf("\n");	
			y++;
		}
	}
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

	if (!(info->texture = malloc(sizeof(int *) * 4)))
		return (MALLOC_ERR);
	i = 0;
	while (i < 4)
	{
		if (!(info->texture[i] = ft_calloc((texHeight * texWidth), sizeof(int))))
			return (MALLOC_ERR);
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
	if (info->mlx == NULL)
		return (MLX_ERR);
	info->posX = map_data->player[X];
	info->posY = map_data->player[Y];
	info->dirX = -1.0;
	info->dirY = 0;
	info->planeX = 0.0;
	info->planeY = 0.66;
	info->moveSpeed = 0.15;
	info->rotSpeed = 0.15;
	info->map_data = map_data;
	info->wc_data = malloc(sizeof(t_wc_data) * 1);
	if (info->wc_data == NULL)
		return (MALLOC_ERR);
	info->fc_data = malloc(sizeof(t_fc_data) * 1);
	if (info->fc_data == NULL)
		return (free(info->wc_data), free(info->mlx), MALLOC_ERR);
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
int	main_loop(t_info *info)
{
	if (calc(info) == MALLOC_ERR)
		return (MALLOC_ERR);
	draw(info);
	//printf("info->dirX: %f | info->dirY: %f\n", info->dirX, info->dirY);
	return (0);
}

int	convert_map(t_map_data *map_data)
{
	int	x;
	int	y;
	
	map_data->map = malloc(sizeof(int *) * map_data->map_size[Y]);
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
	return (EXIT_SUCCESS);
}

void	free_textures(char **str)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		free(str[i]);
		i++;
	}
}

void	free_int(int **tab)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
	t_info *info;
	
	//print_only_map(map_data->map);
	convert_map(map_data);
	info = ft_calloc(1, sizeof(t_info));
	if (info == NULL)
		return (MALLOC_ERR);
	initialize_info_structure(info, map_data);

	info->win = mlx_new_window(info->mlx, width, height, "minecraft4.0");
	info->img.img = mlx_new_image(info->mlx, width, height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_key_hook(info->win, &key_press, info);
	mlx_hook(info->win, 17, 0L, &handle_cross, info);
	mlx_loop(info->mlx);
	mlx_destroy_window(info->mlx, info->win);
	mlx_destroy_image(info->mlx, info->img.img);
	mlx_destroy_display(info->mlx);
	free(info->mlx);
	free_textures(map_data->textures_colours);
	ft_free(map_data->map_char);
	free_int(info->texture);
	free_int(map_data->map);
	free(info->wc_data);
	free(info->fc_data);
	free(info);
	return (EXIT_SUCCESS);
}

