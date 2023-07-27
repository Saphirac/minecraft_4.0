/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:19:43 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/26 22:20:48 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Calculate step and initial sideDist
 * 
 * step_x and step_y are the distance to the next side of a wall
 * 
 * sideDist are initially the distance the ray has to travel
 * from its start position to the first x-side and the 
 * first y-side
 *
 * @param
 * @return
 * @throws
*/
void	calc_step_and_init_sidedist(t_wc_data *data, t_info *info)
{
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->side_dist_x = (info->posX - data->map_x) * data->delta_dist_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1.0 - info->posX) * \
							data->delta_dist_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (info->posY - data->map_y) * data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1.0 - info->posY) * \
							data->delta_dist_y;
	}
}

/**
 * @brief Perform the DDA: DDA is a fast algorithm typically used on square grids
 * to find which squares a line hits
 *

 * delta_dist_x and delta_dist_y are the distance the ray has to 
 * travel to go from 1 x-side to the next x-side, or from 
 * 1 y-side to the next y-side
 *
 * the algorithm choose to jump to next map square, OR in x-direction, 
 * OR in y-directionl
 *
 * Check if ray has hit a wall:
 * if (worldMap[data->map_x][data->map_y] > 0) data->hit = 1;  
 *
 *
 * @param t_wc_data *data: the data structure that store 
 * all variable used for the wall casting
 *
 * @return 
 * @throws
*/
void	dda_algorithm(t_wc_data *data, int **map, t_info *info)
{
	(void)info;
	while (data->hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (map[data->map_y][data->map_x] > 0)
			data->hit = 1;
	}
}

/**
 * @brief calculate lowest and highest pixel to fill in current stripe
 *
 * int draw_start: is the lowest pixel
 * int draw_end: is the highest pixel
 * int lineheight: is the height of line to draw on screen
 *
 * @param t_wc_data *data: the data structure that store 
 * all variable used for the wall casting
 *
 * @return 
 * @throws
*/
void	calc_draw_start_and_draw_end(t_wc_data *data)
{
	data->draw_start = -data->lineheight / 2 + height / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->lineheight / 2 + height / 2;
	if (data->draw_end >= height)
		data->draw_end = height - 1;
}

/**
 * @brief Calculate distance of perpendicular ray 
 * (Euclidean distance would give fisheye effect!)
 * 
 * perp_wall_dist is the perpendicular distance from the player (posX, posY) 
 * to the position (map_x, map_y)
 *
 * @param t_wc_data *data: the data structure that store 
 * all variable used for the wall casting
 *
 * @param t_info *info: the data structure that store core program variable
 *
 * @return 
 * @throws
*/
void	calc_perpendicular_distance(t_wc_data *data, t_info *info)
{
	if (data->side == 0)
		data->perp_wall_dist = (data->map_x - info->posX + \
				(1 - data->step_x) / 2) / data->ray_dir_x;
	else
		data->perp_wall_dist = (data->map_y - info->posY + \
				(1 - data->step_y) / 2) / data->ray_dir_y;
}
