/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:13:59 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/23 11:20:07 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char			*get_perm2(struct stat dp, char *tab)
{
	if ((S_ISDIR(dp.st_mode) != 0))
		tab[0] = 'd';
	if ((S_ISLNK(dp.st_mode) != 0))
		tab[0] = 'l';
	else if ((S_ISFIFO(dp.st_mode) != 0))
		tab[0] = 'p';
	else if ((S_ISSOCK(dp.st_mode) != 0))
		tab[0] = 's';
	else if ((S_ISBLK(dp.st_mode) != 0))
		tab[0] = 'b';
	else if ((S_ISCHR(dp.st_mode) != 0))
		tab[0] = 'c';
	else if ((S_ISDIR(dp.st_mode) != 0))
		tab[0] = 'd';
	else
		tab[0] = '-';
	return (tab);
}

char			*get_perm(struct stat dp)
{
	char		*tab;

	if (!(tab = malloc(sizeof(char) * 11)))
		return (NULL);
	tab[1] = ((dp.st_mode & S_IRUSR) != 0) ? ('r') : ('-');
	tab[2] = ((dp.st_mode & S_IWUSR) != 0) ? ('w') : ('-');
	tab[3] = ((dp.st_mode & S_IXUSR) != 0) ? ('x') : ('-');
	tab[4] = ((dp.st_mode & S_IRGRP) != 0) ? ('r') : ('-');
	tab[5] = ((dp.st_mode & S_IWGRP) != 0) ? ('w') : ('-');
	tab[6] = ((dp.st_mode & S_IXGRP) != 0) ? ('x') : ('-');
	tab[7] = ((dp.st_mode & S_IROTH) != 0) ? ('r') : ('-');
	tab[8] = ((dp.st_mode & S_IWOTH) != 0) ? ('w') : ('-');
	tab[9] = ((dp.st_mode & S_IXOTH) != 0) ? ('x') : ('-');
	tab[10] = '\0';
	if (dp.st_mode & S_ISUID)
		tab[3] = (dp.st_mode & S_IXUSR) ? 's' : 'S';
	if (dp.st_mode & S_ISGID)
		tab[6] = (dp.st_mode & S_IXGRP ? 's' : 'S');
	if (dp.st_mode & S_ISVTX)
		tab[9] = (dp.st_mode & S_IXOTH ? 't' : 'T');
	tab = get_perm2(dp, tab);
	return (tab);
}

char			*ft_getnstr(const char *s, size_t n)
{
	size_t		len;
	size_t		i;
	char		*str;

	str = ft_strdup("\0");
	len = ft_strlen(s);
	i = 0;
	while (i < MIN(len, n))
	{
		str = ft_strjoina(str, s[i]);
		i++;
	}
	return (str);
}

char			*get_time(struct stat *stat)
{
	time_t		now;
	time_t		mtime;
	time_t		diff;
	char		*mtime_str;
	char		*ret_time;

	now = time(NULL);
	mtime = stat->st_mtime;
	mtime_str = ctime(&mtime);
	diff = now - mtime;
	ret_time = ft_strdup("\0");
	ret_time = ft_strjoin(ret_time, ft_getnstr(&(mtime_str[4]), 6));
	ret_time = ft_strjoina(ret_time, ' ');
	if (diff < (-3600 * 24 * 30.5 * 6) || diff > (3600 * 24 * 30.5 * 6))
	{
		ret_time = ft_strjoina(ret_time, ' ');
		ret_time = ft_strjoin(ret_time, ft_getnstr(&(mtime_str[20]), 4));
	}
	else
		ret_time = ft_strjoin(ret_time, ft_getnstr(&(mtime_str[11]), 5));
	return (ret_time);
}
