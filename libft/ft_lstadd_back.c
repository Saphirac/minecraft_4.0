/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 02:26:50 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/29 14:46:21 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_back(t_list *alst, char *const new)
{
	t_list *const	node = ft_lstnew(str, is_quoted);

	if (!node)
		return (EXIT_FAILURE);
	ft_lst_push_back(list, node);
	return (EXIT_SUCCESS);
}
