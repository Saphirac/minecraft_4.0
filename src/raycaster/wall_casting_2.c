/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:18:06 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/08/09 16:20:18 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Calculate height of line to draw on screen
 *
 * @param t_wc_data *data: the data structure that store 
 * all variable used for the wall casting
 *
 * @return 
 * @throws
*/
void	calc_lineheight(t_wc_data *data)
{
		data->lineheight = (int)(HEIGHT / data->perp_wall_dist);
}

/**
 * @brief Texturing calculations: find the right texture in the map 
 *
 * 1 subtracted from it so that texture 0 can be used!
 * 
 * @param t_info *info: the data structure that store core program variable
 *
 * @return 
 * @throws
*/
void	calc_texturing(t_wc_data *data, int **map)
{
	(void)map;
	data->tex_num = data->tex;
}

/**
 * @brief Calculate value of wall_x
 *
 * wall_x is where exactly the wall was hit by the x
 * 
 * @param t_wc_data *data: the data structure that store 
 * all variable used for the wall casting
 *
 * @return 
 * @throws
*/
void	calc_wallx_value(t_wc_data *data, t_info *info)
{
	if (data->side == 0)
		data->wall_x = info->vec_pos[Y] + data->perp_wall_dist * \
						data->ray_dir[Y];
	else
		data->wall_x = info->vec_pos[X] + data->perp_wall_dist * \
						data->ray_dir[X];
	data->wall_x -= floor(data->wall_x);
}

/**
 * @brief Calculate the x coordinate on the texture
 * 
 * @param t_wc_data *data: the data structure that store 

 * all variable used for the wall casting
 *
 * @return 
 * @throws
*/
void	calc_x_coordinate_on_texture(t_wc_data *data)
{
	data->tex_x = (int)(data->wall_x * (double)TEXWIDTH);
	data->tex_x = TEXWIDTH - data->tex_x - 1;
}

/**
 * @brief Calculate the step
 * 
 * step is how much to increase the texture coordinate perscreen pixel
 *
 * @param t_wc_data *data: the data structure that store 
 * all variable used for the wall casting
 *
 * @return 
 * @throws
*/
void	calc_step(t_wc_data *data)
{
	data->step = 1.0 * TEXHEIGHT / data->lineheight;
}
