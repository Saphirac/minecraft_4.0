/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:38:28 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/24 02:05:17 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline static int	__biggest(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

inline static bool	__in_border(int x, int y, t_data *data)
{
	if (x < 0 || x >= data->lg || y < 0 || y >= data->wd)
		return (false);
	return (true);
}

void	draw_line(t_data *data, t_v2i p1, t_v2i p2, int color)
{
	t_v2i	delta;
	int		len;
	t_v2f	inc;
	t_v2f	xy;

	delta = p2 - p1;
	len = __biggest(abs(delta[X]), abs(delta[Y]));
	inc[X] = delta[X] / (float)len;
	inc[Y] = delta[Y] / (float)len;
	xy[X] = p1[X];
	xy[Y] = p1[Y];
	while (len--)
	{
		if (__in_border(xy[X], xy[Y], data) == true)
			img_pix_put(data, (int)xy[X], (int)xy[Y], color);
		xy += inc;
	}
}
