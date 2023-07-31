/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:42:02 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/27 20:35:16 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief initialize all data's variables
 * 
 * @param t_wc_data *data: the data structure that store 
 * all variable used for the wall casting
 *
 * @param t_info *info: the data structure that store core program variable
 *
 * @return 
 * @throws
*/
void	init_data(t_wc_data *data, t_info *info, int x)
{
	data->camera_x = 2 * x / (double)WIDTH - 1;
	data->ray_dir[X] = info->dir_x + info->plane_x * data->camera_x;
	data->ray_dir[Y] = info->dir_y + info->plane_y * data->camera_x;
	data->vec_map[X] = (int)info->pos_x;
	data->vec_map[Y] = (int)info->pos_y;
	data->delta_dist_x = fabs(1 / data->ray_dir[X]);
	data->delta_dist_y = fabs(1 / data->ray_dir[Y]);
	data->hit = 0;
}

/**
 * @brief This function store the right color in info->buf for each pixel
 *
 * texPos is the starting texture coordinate
 * 
 * texY: Cast the texture coordinate to integer, and mask with (texHeight - 1) 
 * in case of overflow
 *
 * color is the color we will print
 *
 * We make color darker for y-sides: R, G and B byte each 
 * divided through two with a "shift" and an "and"
 *
 * @param 
 *
 * @return 
 * @throws
*/
void	draw_texture(t_wc_data *data, t_info *info, int x)
{
	double	tex_pos;
	int		tex_y;
	int		color;
	int		y;

	tex_pos = (data->draw_start - HEIGHT / 2 + data->lineheight / 2) * \
				data->step;
	y = data->draw_start;
	while (y < data->draw_end)
	{
		tex_y = (int)tex_pos & (TEXHEIGHT - 1);
		tex_pos += data->step;
		color = info->texture[data->tex_num][TEXHEIGHT * tex_y + data->tex_x];
		info->buf[y][x] = color;
		y++;
	}
}

/**
 * @brief compute the wall casting i.e the raycasting use to draw the walls
 * 
 * @param t_info *info: the data structure that store core program variable
 *
 * @return 0 if all it's OK else code error
 * @throws MALLOC_ERR if a malloc fail
*/
int	wall_casting(t_info *info)
{
	t_wc_data	*data;
	int			x;

	data = info->wc_data;
	x = 0;
	while (x < WIDTH)
	{
		init_data(data, info, x);
		calc_step_and_init_sidedist(data, info);
		dda_algorithm(data, info->map_data->map);
		calc_perpendicular_distance(data, info);
		calc_lineheight(data);
		calc_step_and_init_sidedist(data, info);
		calc_draw_start_and_draw_end(data);
		calc_texturing(data, info->map_data->map);
		calc_wallx_value(data, info);
		calc_x_coordinate_on_texture(data);
		calc_step(data);
		draw_texture(data, info, x);
		x++;
	}
	return (data = NULL, 0);
}
