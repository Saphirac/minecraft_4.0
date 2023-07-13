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

typedef struct	s_img_data
{
	void	*img;
	char	*addr;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img_data;

typedef struct	s_info
{
	void		*mlx;
	void		*win;
	int			**buf;
	int			**texture;
	double		moveSpeed;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		rotSpeed;
	t_img_data	img_data;
	t_map_data	*map_data;
}				t_info;

int	floor_casting(t_info *info);
int	wall_casting(t_info *info);

#endif
