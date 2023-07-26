/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:33:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/26 22:34:37 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include "map.h"

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17
# define texWidth 64
# define texHeight 64
# define mapWidth 24
# define mapHeight 24
# define width 1920
# define height 1080
# define MALLOC_ERR 2
# define MLX_ERR 3

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

/**
 * @brief t_wc_data *data: the data structure that store 
 * all variable used for the wall casting
 *
 * double camera_x: the ray position
 * 
 * double ray_dir_x, double ray_dir_y: the ray direction
 *
 * int map_x, int map_y: which box we're in
 *
 * double side_dist_x, double side_dist_y: side_dist_x and side_dist_y are 
 * initially the distance the ray has to travel from its start position 
 * to the first x-side and the first y-side
 *
 * double delta_dist_x, double delta_dist_y: length of ray from one x 
 * or y-side to next x or y-side
 *
 * double perp_wall_dist: the perpendicular distance from the player 
 * (posX, posY) to the position (map_x, map_y)
 * 
 * int step_x, int step_y:  step_x and step_y are the distance to the 
 * next side of a wall
 *
 * int hit: was the a wall hit ? we initialize at 0 for "no wall was hit"
 *
 * int side: was a NS or a EW wall hit ?
 *
 * int	draw_start;
 * int	draw_end;
 *
 * int	lineheight;
 * int tex_num;
 * double wall_x;
 * int tex_x;
 * double step;
 *
 */
typedef struct s_wc_data
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		draw_start;
	int		draw_end;
	int		lineheight;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
}				t_wc_data;

/**
 *
 * @brief data structure used in draw_floor function
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
 *
 */
typedef struct s_draw_floor_data
{
	float	floor_x;
	float	floor_y;
	int		x;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		floor_texture;
	int		ceiling_texture;
	int		color;
}				t_draw_floor_data;

/**
 * @brief t_fc_data *data: the data structure that store 
 * all variable used for the floor casting
 *
 * float ray_dir_x0, float ray_dir_y0: ray direction for leftmost i.e.(x = 0)
 *
 * float ray_dir_x1, float ray_dir_y1: ray direction for rightmost 
 * i.e. (x = width)
 *
 * float row_distance: Vertical distance from the camera to the floor for 
 * the current row. 0.5 is the z position exactly in the middle between 
 * floor and ceiling.
 *
 *  
 */
typedef struct s_fc_data
{
	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
}				t_fc_data;

typedef struct	s_info
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	void		*mlx;
	void		*win;
	t_img		img;
	int			buf[height][width];
	int			**texture;
	double		moveSpeed;
	double		rotSpeed;
	t_map_data	*map_data;
	t_wc_data	*wc_data;
	t_fc_data	*fc_data;
}				t_info;

int		floor_casting(t_info *info);
int		wall_casting(t_info *info);
void	print_map_char(t_info *info);

//DEBUG FUNCTIONS
void	print_textures(t_info *info);

#endif
