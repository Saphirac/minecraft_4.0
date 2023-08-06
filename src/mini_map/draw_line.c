/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:04:13 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/08/02 16:04:13 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img img, int x, int y, int color)
{
	((int *)img.data)[x + (y * img.img_height)] = color;
}

inline static int	__biggest(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

inline static bool	__in_border(int x, int y, t_img data)
{
	if (x < 0 || x >= data.img_width || y < 0 || y >= data.img_height)
		return (false);
	return (true);
}

void	draw_line(t_img img, t_v2i p1, t_v2i p2, int colour)
{
	t_v2i	delta;
	size_t	len;
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
		if (__in_border(xy[X], xy[Y], img) == true)
			img_pix_put(img, (int)xy[X], (int)xy[Y], colour);
		xy += inc;
	}
	if (__in_border(xy[X], xy[Y], img) == true)
			img_pix_put(img, (int)xy[X], (int)xy[Y], colour);
}
