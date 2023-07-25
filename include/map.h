/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:07:30 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/25 18:09:58 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cub3d.h"

typedef struct s_map_data		t_map_data;
typedef enum e_texture			t_texture;
typedef struct s_get_texture	t_get_texture;

enum e_texture {
	SO,
	NO,
	WE,
	EA,
	F,
	C,
};

struct s_get_texture
{
	char const *const	name;
	t_texture const		texture;
};

/**
 * @brief map_data struct 
 * char *map : map composition
 * t_v2i map_size : size of the map
 * char *so : south texture
 * char	*no : north texture
 * char	*we : west texture
 * char	*ea : east texture
 * char	*f : floor colour
 * char	*c : ceiling colour
 */
struct s_map_data {
	char	**map_char;
	int		**map;
	t_v2i	map_size;
	char	*textures_colours[6];
	t_v2f	player;
	char	player_orientation;
	int		color_ceiling;
	int		color_floor;
};

char	*get_texture(
			t_map_data *const map,
			char const *const line,
			t_texture const n)
		__attribute__((nonnull));

static t_get_texture const		g_get_texture[] = {
{"SO", SO},
{"NO", NO},
{"WE", WE},
{"EA", EA},
{"F", F},
{"C", C},
{0},
};

#endif
