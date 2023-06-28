/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:21:16 by mcourtoi          #+#    #+#             */
/*   Updated: 2021/12/10 05:20:50 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static char	*ft_rev(char *tab)
{
	size_t	a;
	size_t	b;
	char	swap;

	a = ft_strlen(tab) - 1;
	b = 0;
	if (tab[0] == '-')
		b++;
	while (b < a)
	{
		swap = tab[b];
		tab[b] = tab[a];
		tab[a] = swap;
		a--;
		b++;
	}
	return (tab);
}

static int	ft_size_malloc(long int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*tab;
	long int		a;
	long int		i;

	a = n;
	i = 0;
	tab = malloc(sizeof(char) * (ft_size_malloc(a) + 1));
	if (!tab)
		return (NULL);
	if (a < 0)
	{
		tab[i] = '-';
		a = -a;
		i++;
	}
	while (a > 9)
	{
		tab[i] = (a % 10) + '0';
		a = a / 10;
		i++;
	}
	if (a < 10)
		tab[i] = a + '0';
	tab[i + 1] = '\0';
	return (ft_rev(tab));
}
