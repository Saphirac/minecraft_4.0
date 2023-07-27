/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:29:25 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/26 22:07:24 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_no_event(void *data)
{
	(void)data;
	return (0);
}

int	handle_cross(t_info *info)
{
	(void)info;
	mlx_loop_end(info->mlx);
	return (0);
}

void	key_esc(int key, t_info *info)
{
	if (key == KEY_ESC)
		mlx_loop_end(info->mlx);
}
