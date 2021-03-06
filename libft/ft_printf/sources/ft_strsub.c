/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssicard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:10:06 by ssicard           #+#    #+#             */
/*   Updated: 2016/01/27 23:20:45 by ssicard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	start1;
	size_t	i;

	if (s)
	{
		ptr = (char *)malloc(sizeof(*s) * (len + 1));
		if (ptr == NULL)
			return (NULL);
		i = 0;
		start1 = (size_t)start;
		while (len > i && s[start])
		{
			ptr[i] = s[start];
			i++;
			start++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	return (NULL);
}
