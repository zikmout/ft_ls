/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:22:37 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/20 14:36:11 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void				whi(t_m *m, struct stat dp, t_env *e, DIR *d)
{
	char			*tmp;
	t_data			*data;

	tmp = ft_strdup(m->cur->file_n);
	data = fill_dat(tmp);
	free(tmp);
	if (lstat(m->cur->file_n, &dp) == 0 &&
			e->flags[F_LMIN] == '1' && S_ISLNK(dp.st_mode))
		to_push(e, m->cur->file_n, data, &(m->new0));
	if (!d && (errno == 20 || errno == 2))
		e->first = 1;
	if (!d)
		to_push(e, m->cur->file_n, data, &(m->new1));
	else if (!d && errno == 2)
	{
		ft_putstr("ls: ");
		perror(m->cur->file_n);
	}
	else if (d)
	{
		e->first = 1;
		e->multi_dir = 1;
		to_push(e, m->cur->file_n, data, &(m->new2));
	}
}

t_f					*ls_start_errno(t_f *head, t_env *e)
{
	DIR				*d;
	struct stat		dp;
	t_m				*m;

	m = mutli_lst();
	head = mini_check(e, head, m);
	while (m->cur)
	{
		if (ft_strcmp(m->cur->file_n, ".") == 0 ||
				ft_strcmp(m->cur->file_n, "./") == 0)
			recur(".", e);
		d = opendir(m->cur->file_n);
		whi(m, dp, e, d);
		m->cur = m->cur->next;
	}
	make_sort(&(m->new1), e);
	print_lst(&(m->new0), e);
	print_lst(&(m->new1), e);
	return (m->new2);
}

void				ls_start(t_f *head, t_env *e)
{
	t_f				*cur;

	make_sort(&head, e);
	if (e->flags[F_RMIN] == '1')
		reverse(&head);
	cur = head;
	while (cur)
	{
		recur(cur->file_n, e);
		cur = cur->next;
	}
}

t_f					*new_elem(char *str, t_data *data)
{
	t_f				*new;

	new = NULL;
	if (!(new = (t_f *)malloc(sizeof(t_f))))
		exit(0);
	new->file_n = ft_strdup(str);
	new->data = data;
	new->next = NULL;
	return (new);
}

void				push_back(t_f **begin, char *str, t_data *data)
{
	t_f				*lst;

	lst = new_elem(str, data);
	if (*begin == NULL)
		*begin = lst;
	else
		list_end(*begin)->next = lst;
}
