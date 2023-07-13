/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:29:25 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/12 21:06:17 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_no_event(void *data)
{
	(void)data;
	return (0);
}

int	handle_cross(t_info *data)
{
	mlx_loop_end(data->mlx);
	return (0);
}

int	handle_input(int keysym, t_info *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx);
	return (0);
}
