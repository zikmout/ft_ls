/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:20:26 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/20 14:18:18 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		get_total(t_f **begin)
{
	int	total;
	t_f	*cur;

	total = 0;
	cur = *begin;
	while (cur)
	{
		total = total + cur->data->block;
		cur = cur->next;
	}
	return (total);
}

void	print_lst(t_f **begin, t_env *e)
{
	t_f *cur;

	cur = *begin;
	while (cur)
	{
		if (e->flags[F_IMIN] == '1')
			ft_printf("%9d ", cur->data->inode);
		if (e->flags[F_LMIN] == '1')
		{
			ft_printf("%s %2d %s  %s  ", cur->data->perm, cur->data->n_lnk,
					cur->data->st_uid, cur->data->st_gid);
			if (MAJOR(cur->data->dev) != 0 || MINOR(cur->data->dev) != 0)
				ft_printf("%4d,%6d", MAJOR(cur->data->dev),
						MINOR(cur->data->dev));
			else
				ft_printf("%7u", cur->data->size);
			ft_printf(" %s ", cur->data->mtime);
		}
		ft_printf("%s", cur->file_n);
		if (e->flags[F_LMIN] == '1' && ft_strcmp(cur->data->lnk_p, "\0") != 0)
			ft_printf(" -> %s", cur->data->lnk_p);
		ft_printf("\n");
		cur = cur->next;
	}
}

void	print_lst_rev(t_f *begin, t_env *e)
{
	t_f *cur;

	if (begin == NULL)
		return ;
	else
	{
		print_lst_rev((*begin).next, e);
		if (e->flags[F_IMIN] == '1')
			ft_printf("%9d ", (*begin).data->inode);
		if (e->flags[F_LMIN] == '1')
		{
			ft_printf("%s %2d %s  %s  ", (*begin).data->perm,
					(*begin).data->n_lnk, (*begin).data->st_uid,
					(*begin).data->st_gid);
			ft_printf("%7u %s ", (*begin).data->size, (*begin).data->mtime);
		}
		ft_printf("%s\n", (*begin).file_n);
	}
}

void	free_lst(t_f **begin)
{
	t_f	*cur;
	t_f	*tmp;

	cur = *begin;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
	free(*begin);
}
