/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:10:09 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/17 17:07:13 by gle-mini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline static char	**__populate(
	char **output,
	char *ptr,
	char const *str,
	char const *const set)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		output[i++] = ptr;
		while (*str && !ft_strchr(set, *str))
			*ptr++ = *str++;
		*ptr++ = 0;
		while (*str && ft_strchr(set, *str))
			++str;
	}
	return (output);
}

/*
	Split the given string `str` whenever char `c` is encountered
	Return an array of strings resulting of the spliting
*/
char	**ft_split(char const *str, char const *const set)
{
	register char const	*ptr;
	char				**output;
	size_t				size;
	size_t				len;

	while (*str && ft_strchr(set, *str))
		++str;
	ptr = str;
	size = 0;
	len = 0;
	while (*ptr)
	{
		if (!ft_strchr(set, *ptr))
		{
			++len;
			if (ptr == str || ft_strchr(set, *(ptr - 1)))
				++size;
		}
		++ptr;
	}
	output = malloc((size + 1) * sizeof(char *) + (len + size) * sizeof(char));
	if (!output)
		return (NULL);
	output[size] = NULL;
	return (__populate(output, (char *)(output + size + 1), str, set));
}
