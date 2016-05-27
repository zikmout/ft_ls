/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:19:53 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/20 14:36:12 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int	main(int ac, char **av)
{
	t_env	e;
	t_f		*cur;
	t_f		*cur2;
	int		i;
	int		k;

	i = 1;
	k = 1;
	cur = NULL;
	cur2 = NULL;
	init_s_env(&e);
	if (ac < 1 || (ft_strcmp(av[1], "") == 0 && av[1] != NULL))
	{
		ft_printf("ls: fts_open: No such file or directory\n");
		exit(0);
	}
	if (set_flags(&e, av, i, k) && get_arg_dir(&e, av))
	{
		cur = (*(e.head));
		cur2 = ls_start_errno(cur, &e);
		ls_start(cur2, &e);
	}
	else
		recur(".", &e);
	return (0);
}
