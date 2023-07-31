/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:19:43 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/27 20:37:00 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Calculate step and initial sideDist
 * 
 * vec_step[X] and vec_step[Y] are the distance to the next side of a wall
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
	if (data->ray_dir[X] < 0)
	{
		data->vec_step[X] = -1;
		data->side_dist[X] = (info->pos_x - data->vec_map[X]) * data->delta_dist_x;
	}
	else
	{
		data->vec_step[X] = 1;
		data->side_dist[X] = (data->vec_map[X] + 1.0 - info->pos_x) * \
							data->delta_dist_x;
	}
	if (data->ray_dir[Y] < 0)
	{
		data->vec_step[Y] = -1;
		data->side_dist[Y] = (info->pos_y - data->vec_map[Y]) * data->delta_dist_y;
	}
	else
	{
		data->vec_step[Y] = 1;
		data->side_dist[Y] = (data->vec_map[Y] + 1.0 - info->pos_y) * \
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
 * if (worldMap[data->vec_map[X]][data->vec_map[Y]] > 0) data->hit = 1;  
 *
 *
 * @param t_wc_data *data: the data structure that store 
 * all variable used for the wall casting
 *
 * @return 
 * @throws
*/
void	dda_algorithm(t_wc_data *data, int **map)
{
	while (data->hit == 0)
	{
		if (data->side_dist[X] < data->side_dist[Y])
		{
			data->side_dist[X] += data->delta_dist_x;
			data->vec_map[X] += data->vec_step[X];
			data->side = 0;
			if (data->ray_dir[X] > 0)
				data->tex = 2;
			else
				data->tex = 3;
		}
		else
		{
			data->side_dist[Y] += data->delta_dist_y;
			data->vec_map[Y] += data->vec_step[Y];
			data->side = 1;
			if (data->ray_dir[Y] > 0)
				data->tex = 0;
			else
				data->tex = 1;
		}
		if (map[data->vec_map[Y]][data->vec_map[X]] > 0)
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
	data->draw_start = -data->lineheight / 2 + HEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->lineheight / 2 + HEIGHT / 2;
	if (data->draw_end >= HEIGHT)
		data->draw_end = HEIGHT - 1;
}

/**
 * @brief Calculate distance of perpendicular ray 
 * (Euclidean distance would give fisheye effect!)
 * 
 * perp_wall_dist is the perpendicular distance from the player (posX, posY) 
 * to the position (vec_map[X], vec_map[Y])
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
		data->perp_wall_dist = (data->vec_map[X] - info->pos_x + \
				(1 - data->vec_step[X]) / 2) / data->ray_dir[X];
	else
		data->perp_wall_dist = (data->vec_map[Y] - info->pos_y + \
				(1 - data->vec_step[Y]) / 2) / data->ray_dir[Y];
}
