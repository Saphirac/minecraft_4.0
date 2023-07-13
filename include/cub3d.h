/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:56:10 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/12 21:32:29 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "vectors.h"
# include "get_next_line.h"
# include "map.h"
# include "str_lst.h"
# include "raycasting.h"
# include "key_linux.h"

# include <stdlib.h>
# include <stdio.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include <time.h>

# define MINI_MAP_SIZE 2

typedef struct s_data {
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		lg;
	int		wd;
}				t_data;

// Keys events //

int		handle_no_event(void *data);
int		handle_input(int keysym, t_info *data);
int		handle_cross(t_info *data);
int		key_press(int key, t_info *info);

// Drawing //

void	img_pix_put(t_img_data **img, int x, int y, int color)
		__attribute__((always_inline));
void	draw_line(t_img_data **img, t_v2i p1, t_v2i p2, int color);
void	draw_mini_map(t_img_data **img, t_map_data *map);
char	get_block(t_map_data *map, t_v2i pos);

// Parsing //

char	**copy_map(char **map);
int		max(int a, int b);
int		min(int a, int b);
int		find_max_x(char **map);
bool	is_correct_char(char c);
int		get_all_data(t_map_data *const map, int const fd);
int		ft_arrstrlen(char **array);
void	ft_free(char **tab);
void	print_map(t_map_data *map);
int		get_map(t_map_data *map, int fd, char *line);
int		open_file(char const *const file);
bool	is_line_empty(char const *const line);
bool	is_textures_full(t_map_data *map);
bool	check_border(t_map_data *map);
int		find_player(t_map_data *map);
void 	print_only_map(t_map_data *map);

// Raycasting //
int		raycaster(t_info *info, t_map_data *map_data);
int		initialize_info_structure(t_info *info, t_map_data *map_data);
int		initialize_textures(t_info *info, t_img_data *img, t_map_data *map);

#endif
