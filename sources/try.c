/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 13:00:54 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/07 15:08:36 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int					recur3(t_env *e, DIR *d, char *dn, t_f **head)
{
	struct dirent	*entry;
	char			*tmp;
	t_data			*data;

	entry = readdir(d);
	while (42)
	{
		tmp = ft_strjoin(dn, "/");
		tmp = ft_strjoin(tmp, entry->d_name);
		if (!(data = fill_dat(tmp)))
			return (1);
		to_push(e, entry->d_name, data, head);
		if ((entry = readdir(d)) == NULL)
			break ;
	}
	return (0);
}

int					recur(char *dn, t_env *e)
{
	DIR				*d;
	struct dirent	*entry;
	t_f				*head;
	char			*tmp;
	struct stat		dp;

	head = NULL;
	d = opendir(dn);
	if (e->flags[F_LMIN] == '1' && lstat(dn, &dp) == 0 && S_ISLNK(dp.st_mode))
		return (0);
	if (!d && (errno == 20 || errno == 2))
		return (1);
	if (d)
	{
		if (recur3(e, d, dn, &head))
			return (1);
		show_list(e, dn, &head);
	}
	else if (errno == 13)
		return (print_error(e, dn));
	if (e->flags[F_RMAJ] == '1')
		recur2(head, e, dp, dn);
	closedir(d);
	return (0);
}

void				recur2(t_f *head, t_env *e, struct stat dp, char *dir_name)
{
	char			*tmp;

	ft_putchar('\n');
	while (head)
	{
		tmp = ft_strjoin(dir_name, "/");
		tmp = ft_strjoin(tmp, head->file_n);
		if (lstat(tmp, &dp) == 0)
		{
			if (S_ISDIR(dp.st_mode) && ft_strcmp(head->file_n, ".") != 0
					&& ft_strcmp(head->file_n, "..") != 0)
				recur(tmp, e);
		}
		free(tmp);
		head = head->next;
	}
}

int					print_error(t_env *e, char *dir_name)
{
	char			*str;

	printf("%s:\nls: ", dir_name);
	str = get_fn(dir_name);
	perror(str);
	ft_putchar('\n');
	return (2);
}

void				print_top_lst(t_env *e, char *dir_name)
{
	if (e->flags[F_RMAJ] == '1' && e->first == 0)
		e->first = 1;
	else if (e->first == 1)
	{
		if (dir_name[0] == '/' && dir_name[1] == '/')
			printf("%s:\n", dir_name + 1);
		else
			printf("%s:\n", dir_name);
	}
}
