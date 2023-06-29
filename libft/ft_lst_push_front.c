/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:41:46 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/29 14:47:33 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push_front(t_list *list, t_list *const node)
{
	if (!list->size)
		list->tail = node;
	else
	{
		node->next = list->head;
		list->head->prev = node;
	}
	list->head = node;
	++list->size;
}
