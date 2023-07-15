#ifndef RAYCASTING_H
# define RAYCASTING_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define width 1920
#define height 1080
#define MALLOC_ERR 2
#define MLX_ERR 3

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

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	t_img	img;
	int		buf[height][width];
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;
	t_map_data	*map_data;
}				t_info;

int		floor_casting(t_info *info);
int		wall_casting(t_info *info);
void	print_map_char(t_info *info);


//DEBUG FUNCTIONS
void	print_textures(t_info *info);

#endif
