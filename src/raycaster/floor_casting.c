/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:45:41 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/18 11:30:13 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Caculate row_distance
 *
 *
 * int p: p is the current pixel distance from the screen center (the horizon)
 *
 * float posZ: the vertical distance from camera to the floor for the 
 * current row i.e. the vertical position of the camera
 *
 * float row_distance: Vertical distance from the camera to the floor for 
 * the current row. 0.5 is the z position exactly in the middle between 
 * floor and ceiling.
 *
 * @param t_fc_data *data: the data structure that store 
 * all variable used for the floor casting
 *
 * @return
 * @throws
 */
void	calc_row_distance(t_fc_data *data, int y)
{
	int		p;
	float	pos_z;

	p = y - height / 2;
	pos_z = 0.5 * height;
	data->row_distance = pos_z / p;
}

/**
 * @brief Calculate ray direction for leftmost ray (x = 0) and 
 * rightmost ray (x = w)
 *
 * @param t_fc_data *data: the data structure that store 
 * all variable used for the floor casting
 *
 * @param t_info *info: the data structure that store core program variable
 *
 * @return
 * @throws
 */
void	calc_ray_direction(t_fc_data *data, t_info *info)
{
	data->ray_dir_x0 = info->dirX - info->planeX;
	data->ray_dir_y0 = info->dirY - info->planeY;
	data->ray_dir_x1 = info->dirX + info->planeX;
	data->ray_dir_y1 = info->dirY + info->planeY;
}

/**
 * @brief calculate the real world step vector we have to add for each x 
 * (parallel to camera plane) adding step by step avoids multiplications 
 * with a weight in the inner loop
 *
 * @param t_fc_data *data: the data structure that store 
 * all variable used for the floor casting
 *
 * 
 * @return
 * @throws
 */
void	calc_floor_step(t_fc_data *data)
{
	data->floor_step_x = data->row_distance * \
						(data->ray_dir_x1 - data->ray_dir_x0) / width;
	data->floor_step_y = data->row_distance * \
						(data->ray_dir_y1 - data->ray_dir_y0) / width;
}


/**
 *
 * @brief 
 *
 * @param
 * @return
 * @throws
 *
 */
void	calc_floor_texture(t_fc_data *data, t_draw_floor_data *draw_data)
{
	draw_data->cell_x = (int)(draw_data->floor_x);
	draw_data->cell_y = (int)(draw_data->floor_y);
	draw_data->tx = (int)(texWidth * \
			(draw_data->floor_x - draw_data->cell_x)) & (texWidth - 1);
	draw_data->ty = (int)(texHeight * \
			(draw_data->floor_y - draw_data->cell_y)) & (texHeight - 1);
	draw_data->floor_x += data->floor_step_x;
	draw_data->floor_y += data->floor_step_y;
	draw_data->floor_texture = 5;
	draw_data->ceiling_texture = 5;
}

/**
 * @brief This function store the right color in info->buf for each pixel
 *
 * float floor_y, float floor_x: are real world coordinates of the leftmost 
 * column. This will be updated as we step to the right.
 *
 * int cell_x, int cell_y: the cell coord is simply got from the integer 
 * parts of floor_x and floor_y
 *
 * int tx, int ty: are used to get the texture coordinate from the fractional 
 * part
 *
 * int floor_texture: the texture's number for the floor
 *
 * int ceiling_texture: the texture's number for the ceiling
 *
 * int color: pixel's color
 *
 * info->buf: the buffer image where we stock our pixel before to print it
 *
 * color = (color >> 1) & 8355711; is used to make a bit darker and simulate
 * basic shadow 
 *
 * @param 
 * @return
 * @throws
 */
int	draw_floor(t_fc_data *data, t_info *info, int y)
{
	t_draw_floor_data	*draw_data;
	int					x;

	draw_data = ft_calloc(1, sizeof(t_draw_floor_data));
	if (draw_data == NULL)
		return (MALLOC_ERR);
	x = 0;
	draw_data->floor_x = info->posX + data->row_distance * data->ray_dir_x0;
	draw_data->floor_y = info->posY + data->row_distance * data->ray_dir_y0;
	while (x < width)
	{
		calc_floor_texture(data, draw_data);
		draw_data->color = info->texture[draw_data->floor_texture][texWidth * \
							draw_data->ty + draw_data->tx];
		//draw_data->color = (draw_data->color >> 1) & 8355711;
		info->buf[y][x] = draw_data->color;
		draw_data->color = info->texture[draw_data->ceiling_texture] \
							[texWidth * draw_data->ty + draw_data->tx];
		//draw_data->color = (draw_data->color >> 1) & 8355711;
		info->buf[height - y - 1][x] = draw_data->color;
		x++;
	}
	free(draw_data);
	return (1);
}

/**
 *
 * @brief compute the floor casting i.e the raycasting use to draw the floor
 * 
 * @param t_info *info: the data structure that store core program variable
 *
 * @return 0 if all it's OK else code error
 * @throws MALLOC_ERR if a malloc fail
 */
int	floor_casting(t_info *info)
{
	t_fc_data	*data;
	int			y;

	y = 0;
	data = info->fc_data;
	if (data == NULL)
		return (MALLOC_ERR);
	while (y < height)
	{
		calc_ray_direction(data, info);
		calc_row_distance(data, y);
		calc_floor_step(data);
		draw_floor(data, info, y);
		y++;
	}
	data = NULL;
	return (0);
}
