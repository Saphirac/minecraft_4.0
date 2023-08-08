/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-mini <gle-mini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 01:56:10 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/27 20:09:41 by gle-mini         ###   ########.fr       */
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
}				t_data;

// Keys events //

int		handle_no_event(void *data);
int		handle_cross(t_info *info);
int		key_press(int key, t_info *info);
void	key_esc(int key, t_info *info);
void	key_d(int key, t_info *info);
void	key_a(int key, t_info *info);
void	key_w(int key, t_info *info);
void	key_s(int key, t_info *info);

// Drawing //

void	img_pix_put(t_data *img, int x, int y, int color)
		__attribute__((always_inline));
void	draw_line(t_data *data, t_v2i p1, t_v2i p2, int color);
void	draw_mini_map(t_data *img, t_map_data *map);
char	get_block(t_map_data *map, t_v2i pos);

// Parsing //

char	**copy_map(char **map);
int		max(int a, int b);
int		min(int a, int b);
int		find_max_x(char **map);
bool	is_correct_char(char c);
int		get_all_data(t_map_data *const map, int const fd);
int		ft_arrstrlen(char **array);
void	print_map(t_map_data *map);
int		get_map(t_map_data *map, int fd, char *line);
int		open_file(char const *const file);
bool	is_line_empty(char const *const line);
bool	is_textures_full(t_map_data *map);
bool	check_border(t_map_data *map);
int		find_player(t_map_data *map);
void	print_only_map(char **map);
int		get_color_ceiling_floor(t_map_data *map_data);
char	**create_map_tmp(t_map_data *src);

// Raycasting //
int		raycaster(t_map_data *map_data);
void	calc_step(t_wc_data *data);
void	calc_x_coordinate_on_texture(t_wc_data *data);
void	calc_wallx_value(t_wc_data *data, t_info *info);
void	calc_texturing(t_wc_data *data, int **map);
void	calc_lineheight(t_wc_data *data);
void	calc_step_and_init_sidedist(t_wc_data *data, t_info *info);
void	dda_algorithm(t_wc_data *data, int **map);
void	calc_draw_start_and_draw_end(t_wc_data *data);
void	calc_perpendicular_distance(t_wc_data *data, t_info *info);
int		initialize_info_structure(t_info *info, t_map_data *map_data);
int		draw_floor(t_fc_data *data, t_info *info, int y);

// Free //
void	free_textures(char **str);
void	free_int(int **tab);
void	free_all(t_map_data *map_data, t_info *info);
void	ft_free(char **tab);
void	ft_free_int_tab(int **tab);

#endif
