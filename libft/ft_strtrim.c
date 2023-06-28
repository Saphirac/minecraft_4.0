/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:58:40 by mcourtoi          #+#    #+#             */
/*   Updated: 2021/12/10 04:48:59 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tab;
	size_t	i;
	size_t	n;
	size_t	s;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && ft_isset(set, s1[i]) == 1)
		i++;
	n = ft_strlen(s1);
	while (n > i && ft_isset(set, s1[n - 1]) == 1)
		n--;
	tab = malloc(sizeof(char) * ((n - i) + 1));
	if (!tab)
		return (NULL);
	s = 0;
	while (i < n)
		tab[s++] = s1[i++];
	tab[s] = '\0';
	return (tab);
}
