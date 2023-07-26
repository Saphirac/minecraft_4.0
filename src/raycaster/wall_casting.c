/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:42:02 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/16 16:11:49 by gle-mini         ###   ########.fr       */
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
void	dda_algorithm(t_wc_data *data, char **map, t_info *info)
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
			if (data->ray_dir_y < 0)
				data->side = 1;
			else
				data->side = 2;
		}
		//printf("DDA | data->map_x:%d | data->map_y:%d\n", data->map_x, data->map_y);
		//print_map_char(info);
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
	data->camera_x = 2 * x / (double)width - 1;
	data->ray_dir_x = info->dirX + info->planeX * data->camera_x;
	data->ray_dir_y = info->dirY + info->planeY * data->camera_x;
	//printf("info->posX:%f | info->posY:%f\n", info->posX, info->posY);
	data->map_x = (int)info->posX;
	data->map_y = (int)info->posY;
	//printf("data->map_x:%d | data->map_y:%d\n", data->map_x, data->map_y);
	//data->side_dist_x;
	//data->side_dist_y;
	data->delta_dist_x = fabs(1 / data->ray_dir_x);
	data->delta_dist_y = fabs(1 / data->ray_dir_y);
	//data->perp_wall_dist;
	//data->step_x;
	//data->step_y;
	data->hit = 0;
	//data->side;
}

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
		data->lineheight = (int)(height / data->perp_wall_dist);
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
void	calc_texturing(t_wc_data *data, char **map)
{
	//TODO: Change calc_texturing with NO SO EA WE
	(void)map;
	data->tex_num = data->side;
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
		data->wall_x = info->posY + data->perp_wall_dist * data->ray_dir_y;
	else
		data->wall_x = info->posX + data->perp_wall_dist * data->ray_dir_x;
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
	data->tex_x = (int)(data->wall_x * (double)texWidth);
	data->tex_x = texWidth - data->tex_x - 1;
	//printf("tex_x:%d\n", data->tex_x);
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
	data->step = 1.0 * texHeight / data->lineheight;
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

	tex_pos = (data->draw_start - height / 2 + data->lineheight / 2) * \
				data->step;
	y = data->draw_start;
	while (y < data->draw_end)
	{
		tex_y = (int)tex_pos & (texHeight - 1);
		tex_pos += data->step;
		color = info->texture[data->tex_num][texHeight * tex_y + data->tex_x];
		//color = info->texture[data->tex_num][texHeight * tex_y + data->tex_x];
		if (data->side == 1)
			color = (color >> 1) & 8355711;
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
	//printf("info player| x: %f | y: %f\n", info->posX, info->posY);
	while (x < width)
	{
		init_data(data, info, x);
		//printf("data->map_x:%d | data->map_y:%d\n", data->map_x, data->map_y);
		calc_step_and_init_sidedist(data, info);
		dda_algorithm(data, info->map_data->map, info);
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
	//free(data);
	data = NULL;
	return (0);
}
