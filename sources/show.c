/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:59:46 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/07 15:09:36 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void				show_list(t_env *e, char *dir_name, t_f **head)
{
	int				total;

	total = 0;
	print_top_lst(e, dir_name);
	make_sort(head, e);
	if (e->flags[F_LMIN] == '1')
		total = get_total(head);
	if (e->flags[F_LMIN] == '1' && *head != NULL)
		ft_printf("total %u\n", total);
	if (e->flags[F_RMIN] == '1')
		reverse(head);
	print_lst(head, e);
	if (e->multi_dir == 1)
		ft_putchar('\n');
}

void				to_push(t_env *e, char *d_name, t_data *data, t_f **head)
{
	if (e->flags[F_AMIN] == '1')
		push_back(head, d_name, data);
	else if (ft_strcmp(".", d_name) != 0 &&
			ft_strcmp("..", d_name) != 0 && d_name[0] != '.')
		push_back(head, d_name, data);
}

t_data				*fill_dat2(char *d_name, struct stat dp, t_data *data)
{
	char			*link;

	data->size = dp.st_size;
	data->mtime = get_time(&dp);
	data->block = dp.st_blocks;
	data->inode = dp.st_ino;
	data->t_stp = (long long)dp.st_mtimespec.tv_sec;
	data->t_stp2 = (long long)dp.st_mtimespec.tv_nsec;
	data->dev = dp.st_rdev;
	data->lnk_p = ft_strdup("\0");
	if (S_ISLNK(dp.st_mode))
	{
		if (!(link = (char *)malloc(sizeof(char) * 256)))
			return (NULL);
		if (readlink(d_name, link, 256))
			data->lnk_p = ft_strdup(link);
		free(link);
	}
	return (data);
}

t_data				*fill_dat(char *d_name)
{
	t_data			*data;
	struct stat		dp;
	struct passwd	*pwd;
	struct group	*grp;

	if (!(pwd = malloc(sizeof(*pwd))))
		return (NULL);
	if (!(grp = malloc(sizeof(*grp))))
		return (NULL);
	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	lstat(d_name, &dp);
	data->perm = get_perm(dp);
	data->n_lnk = dp.st_nlink;
	if (!(pwd = getpwuid(dp.st_uid)))
		return (NULL);
	data->st_uid = ft_strdup(pwd->pw_name);
	if (!(grp = getgrgid(dp.st_gid)))
		return (NULL);
	data->st_gid = ft_strdup(grp->gr_name);
	data = fill_dat2(d_name, dp, data);
	return (data);
}
