/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 16:22:03 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/07 16:28:23 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_m			*mutli_lst(void)
{
	t_m		*m;

	m = malloc(sizeof(*m));
	m->new1 = NULL;
	m->new0 = NULL;
	m->new2 = NULL;
	m->cur = NULL;
	return (m);
}

t_f			*mini_check(t_env *e, t_f *head, t_m *m)
{
	if (e->flags[F_RMIN] == '1')
		reverse(&head);
	else
		make_sort(&head, e);
	m->cur = head;
	return (head);
}

t_f			*list_end(t_f *lst)
{
	if (lst->next == NULL)
		return (lst);
	return (list_end(lst->next));
}
