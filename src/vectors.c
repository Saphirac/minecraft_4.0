/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:13:47 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/24 04:52:40 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

inline float	v2f_mag(t_v2f vec)
{
	vec *= vec;
	return (sqrtf(vec[X] + vec[Y]));
}

inline t_v2f	v2f_norm(t_v2f vec, float lenght)
{
	return ((vec / v2f_mag(vec)) * lenght);
}
