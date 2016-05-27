/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:18:14 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/07 12:19:18 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			check_flag(char c)
{
	int		i;

	i = 0;
	while (i < NB_FLAGS)
	{
		if (c == VALID_FLAGS[i])
			return (1);
		i++;
	}
	ft_usage(c);
	return (0);
}

void		ft_usage(char c)
{
	ft_putstr_fd("ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage : ls [Railrt] [file ...]\n", 2);
	exit(0);
}

char		*get_fn(char *dir_name)
{
	size_t	len;
	size_t	i;
	char	*str;

	str = ft_strdup("\0");
	len = ft_strlen(dir_name);
	i = len;
	while (dir_name[i] != '/' && i > 0)
		i--;
	i++;
	while (dir_name[i])
	{
		str = ft_strjoina(str, dir_name[i]);
		i++;
	}
	return (str);
}

void		print_arg_dir(t_list **begin)
{
	t_list	*cur;

	cur = *begin;
	while (cur)
	{
		ft_putstr(cur->content);
		ft_putchar('\n');
		cur = cur->next;
	}
}
