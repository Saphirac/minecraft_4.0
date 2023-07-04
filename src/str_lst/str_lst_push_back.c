/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:42:48 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/01 21:19:12 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Add a given node at the end of str_lst.
 * 
 * @param list str_lst we add a node to.
 * @param node the node to add.
 * @return t_str* pointer to the new node.
 */
t_str	*str_lst_push_back(t_str_lst *const list, t_str *const node)
{
	if (!list->size)
	{
		list->head = node;
		list->max_line_size = ft_strlen(node->str);
	}
	else
	{
		list->tail->next = node;
		node->prev = list->tail;
		if (ft_strlen(node->str) > list->max_line_size)
			list->max_line_size = ft_strlen(node->str);
	}
	list->tail = node;
	++list->size;
	return (node);
}
