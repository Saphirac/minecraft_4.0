/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:35:03 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/01 20:41:03 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Add a new node to the beginning of str_lst list.
 * 
 * @param list the list we add a node to.
 * @param str string of the new node.
 * @param is_quoted bool determining if node is quoted or not.
 * @return t_str* pointer to the new node.
 */
t_str	*str_lst_add_front(
	t_str_lst *const list,
	char *const str)
{
	t_str *const	node = str_new(str);

	if (!node)
		return (NULL);
	return (str_lst_push_front(list, node));
}
