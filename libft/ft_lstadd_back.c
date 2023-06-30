/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 02:26:50 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/30 15:38:56 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_back(t_list *alst, char *const new)
{
	t_list *const	node = ft_lstnew(new);

	if (!node)
		return (EXIT_FAILURE);
	ft_lst_push_back(alst, node);
	return (EXIT_SUCCESS);
}
