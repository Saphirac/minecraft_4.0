/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 02:24:11 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/30 15:38:27 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_front(t_list *alst, char *const new)
{
	t_list *const	node = ft_lstnew(new);

	if (!node)
		return (EXIT_FAILURE);
	ft_lst_push_front(alst, node);
	return (EXIT_SUCCESS);
}

