/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:07:43 by gle-mini          #+#    #+#             */
/*   Updated: 2023/07/27 20:34:37 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief This function store the right color in info->buf for each pixel
 *
 * float floor[Y], float floor[X]: are real world coordinates of the leftmost 
 * column. This will be updated as we step to the right.
 *
 * int cell_x, int cell_y: the cell coord is simply got from the integer 
 * parts of floor[X] and floor[Y]
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
	draw_data->floor[X] = info->pos_x + data->row_distance * data->ray_dir_x0;
	draw_data->floor[Y] = info->pos_y + data->row_distance * data->ray_dir_y0;
	while (x < WIDTH)
	{
		info->buf[y][x] = info->map_data->color_floor;
		info->buf[HEIGHT - y - 1][x] = info->map_data->color_ceiling;
		x++;
	}
	free(draw_data);
	return (1);
}
