/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:45:41 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/27 20:34:06 by gle-mini         ###   ########.fr       */
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

	p = y - HEIGHT / 2;
	pos_z = 0.5 * HEIGHT;
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
	data->ray_dir_0[X] = info->vec_dir[X] - info->vec_plane[X];
	data->ray_dir_0[Y] = info->vec_dir[Y] - info->vec_plane[Y];
	data->ray_dir_1[X] = info->vec_dir[X] + info->vec_plane[X];
	data->ray_dir_1[Y] = info->vec_dir[Y] + info->vec_plane[Y];
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
	data->floor_step[X] = data->row_distance * \
						(data->ray_dir_1[X] - data->ray_dir_0[X]) / WIDTH;
	data->floor_step[Y] = data->row_distance * \
						(data->ray_dir_1[Y] - data->ray_dir_0[Y]) / WIDTH;
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
	draw_data->cell[X] = (int)(draw_data->floor[X]);
	draw_data->cell[Y] = (int)(draw_data->floor[Y]);
	draw_data->vec_t[X] = (int)(TEXWIDTH * \
			(draw_data->floor[X] - draw_data->cell[X])) & (TEXWIDTH - 1);
	draw_data->vec_t[Y] = (int)(TEXHEIGHT * \
			(draw_data->floor[Y] - draw_data->cell[Y])) & (TEXHEIGHT - 1);
	draw_data->floor[X] += data->floor_step[X];
	draw_data->floor[Y] += data->floor_step[Y];
	draw_data->floor_texture = 5;
	draw_data->ceiling_texture = 5;
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
	while (y < HEIGHT)
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
