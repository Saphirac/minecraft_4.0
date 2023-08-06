/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 21:31:15 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/08/06 22:23:24 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_filename_ok(char const *const file)
{
	int	i;

	i = ft_strlen(file);
	if (i >= 5 && file[i - 1] == 'b' && file[i - 2] == 'u'
		&& file[i - 3] == 'c' && file[i - 4] == '.')
		return (true);
	return (false);
}

int	open_file(char const *const file)
{
	int	fd;

	if (is_filename_ok(file) == false)
		return (printf("Incorrect filename.\n"), -1);
	fd = open(file, O_RDWR);
	return (fd);
}
