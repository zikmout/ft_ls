/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:25:12 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/07 16:39:31 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_f		*merge(t_f *lg, t_f *ld, t_env *e)
{
	if (lg == NULL)
		return (ld);
	else if (ld == NULL)
		return (lg);
	else if ((e->flags[F_TMIN] == '1' && lg->data->t_stp > ld->data->t_stp) ||
			(e->flags[F_TMIN] == '0' && ft_strcmp(lg->file_n, ld->file_n) <= 0))
	{
		lg->next = merge(lg->next, ld, e);
		return (lg);
	}
	else if ((e->flags[F_TMIN] == '1' && (lg->data->t_stp == ld->data->t_stp &&
					lg->data->t_stp2 == ld->data->t_stp2)
				&& ft_strcmp(lg->file_n, ld->file_n) <= 0) || (e->flags[F_TMIN]
				== '1' && (lg->data->t_stp == ld->data->t_stp
					&& lg->data->t_stp2 > ld->data->t_stp2)))
	{
		lg->next = merge(lg->next, ld, e);
		return (lg);
	}
	else
	{
		ld->next = merge(lg, ld->next, e);
		return (ld);
	}
}

t_f		*merge_rev(t_f *lg, t_f *ld, t_env *e)
{
	if (lg == NULL)
		return (ld);
	else if (ld == NULL)
		return (lg);
	else if ((e->flags[F_TMIN] == '1' && lg->data->t_stp < ld->data->t_stp) ||
			(e->flags[F_TMIN] == '0' && ft_strcmp(lg->file_n, ld->file_n) > 0)
			|| (e->flags[F_TMIN] == '1' && (lg->data->t_stp == ld->data->t_stp
					&& lg->data->t_stp2 == ld->data->t_stp2)))
	{
		lg->next = merge_rev(lg->next, ld, e);
		return (lg);
	}
	else if ((e->flags[F_TMIN] == '1' && (lg->data->t_stp == ld->data->t_stp
					&& lg->data->t_stp2 <= ld->data->t_stp2)))
	{
		lg->next = merge(lg->next, ld, e);
		return (lg);
	}
	else
	{
		ld->next = merge_rev(lg, ld->next, e);
		return (ld);
	}
}

t_f		*split(t_f *list, t_env *e)
{
	t_f *aux;

	if (list == NULL || list->next == NULL)
		return (NULL);
	else
	{
		aux = list->next;
		list->next = aux->next;
		aux->next = split(aux->next, e);
		return (aux);
	}
}

void	make_sort(t_f **head, t_env *e)
{
	t_f *aux;

	if (*head != NULL)
		if ((*head)->next != NULL)
		{
			aux = split(*head, e);
			make_sort(head, e);
			make_sort(&aux, e);
			*head = merge(*head, aux, e);
		}
}

void	reverse(t_f **head)
{
	t_f	*prev;
	t_f	*current;
	t_f	*next;

	prev = NULL;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}
