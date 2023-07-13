/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:31:51 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/12 21:34:26 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img_data **img, int x, int y, int color)
{
	((int *)(*img)->addr)[x + (y * width)] = color;
}

	// ((int *)(*img->addr))[x + (y * width)] = color;

