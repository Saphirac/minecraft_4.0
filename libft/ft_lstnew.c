/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 02:23:25 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/06/29 14:50:54 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *str)
{
	t_list *const	output = malloc(sizeof(t_list));

	if (!output)
		return (NULL);
	output->str = ft_strdup(str);
	if (!output->str)
		return (free(output), NULL);
	output->next = NULL;
	output->prev = NULL;
	return (output);
}
