/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:32:11 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/01 20:09:55 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Clear the given str_lst
 * 
 * @param list the str_lst to clear.
 */
void	str_lst_clear(t_str_lst *const list)
{
	while (list->size)
		str_lst_del_one(list, list->head);
}
