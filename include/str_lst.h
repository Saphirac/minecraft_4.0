/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:45:54 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/07/01 20:34:34 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_LST_H
# define STR_LST_H

typedef struct s_str		t_str;
typedef struct s_str_lst	t_str_lst;

struct s_str_lst
{
	t_str	*head;
	t_str	*tail;
	size_t	max_line_size;
	size_t	size;
};

struct s_str
{
	char	*str;
	t_str	*next;
	t_str	*prev;
};

void	str_lst_clear(t_str_lst *const list);
void	str_lst_del_one(t_str_lst *const list, t_str *const node);
t_str	*str_lst_add_back(
			t_str_lst *const list,
			char *const str)
		__attribute__((nonnull));
t_str	*str_lst_add_front(
			t_str_lst *const list,
			char *const str)
		__attribute__((nonnull));
t_str	*str_lst_push_back(t_str_lst *const list, t_str *const node)
		__attribute__((nonnull));
t_str	*str_lst_push_front(t_str_lst *const list, t_str *const node)
		__attribute__((nonnull));
t_str	*str_new(char *const str)
		__attribute__((nonnull));

#endif
