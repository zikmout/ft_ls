/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:55:16 by ssicard           #+#    #+#             */
/*   Updated: 2016/05/20 14:18:19 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		init_s_env(t_env *e)
{
	char	*flags;

	flags = (char *)malloc(sizeof(char) * NB_FLAGS);
	ft_memset(flags, '0', NB_FLAGS);
	e->flags = flags;
	e->first = 0;
	e->multi_dir = 0;
}

int			set_flags(t_env *e, char **av, int i, int k)
{
	int		j;

	if (av[i])
	{
		while (av[i] && av[i][0] == '-')
		{
			check_flag(av[i][k]);
			j = 0;
			while (av[i][k] && j < NB_FLAGS)
			{
				check_flag(av[i][k]);
				if (av[i][k] == VALID_FLAGS[j])
				{
					e->flags[j] = '1';
					k++;
					j = -1;
				}
				j++;
			}
			k = 1;
			i++;
		}
		return (1);
	}
	return (0);
}

int			get_arg_dir(t_env *e, char **av)
{
	int		i;
	int		k;

	k = 0;
	i = 1;
	while (av[i] && av[i][0] == '-')
		i++;
	k = get_arg_dir2(i, k, av, e);
	if (k != 0)
		return (1);
	return (0);
}

int			get_arg_dir2(int i, int k, char **av, t_env *e)
{
	t_f		*head;
	t_data	*data;
	char	*tmp;
	int		j;

	data = NULL;
	head = NULL;
	while (av[i])
	{
		tmp = ft_strdup("\0");
		j = 0;
		while (av[i][j])
		{
			tmp = ft_strjoina(tmp, av[i][j]);
			j++;
			k++;
		}
		if (!(data = malloc(sizeof(t_data *))))
			return (0);
		push_back(&head, tmp, data);
		free(tmp);
		i++;
	}
	e->head = &head;
	return (k);
}
