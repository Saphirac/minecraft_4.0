/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 21:31:15 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/29 21:59:14 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_filename_ok(char const *const file)
{
	
}

int	open_file(char const *const file)
{
	int	fd;

	if (is_filename_ok(file) == false)
		return (-1);
	fd = open(file, O_RDWR);
	return (fd);
}
