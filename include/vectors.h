/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 13:19:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/24 05:10:42 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <math.h>

typedef int		t_v2i __attribute__ ((vector_size (8)));
typedef float	t_v2f __attribute__ ((vector_size (8)));

enum	e_X_Y {
	X,
	Y,
}			;

float	v2f_mag(t_v2f vec)
		__attribute__((always_inline));
t_v2f	v2f_norm(t_v2f vec, float lenght)
		__attribute__((always_inline));

#endif
