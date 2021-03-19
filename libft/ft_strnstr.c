/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:54:08 by ymanzi            #+#    #+#             */
/*   Updated: 2019/10/23 13:55:50 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*b;
	char	*l;

	i = -1;
	b = (char *)big;
	l = (char *)little;
	if (!(*l))
		return (b);
	while (b[++i] && i <= len)
	{
		j = 0;
		while ((big[i + j] == l[j] || l[j] == 0) && (i + j) <= len)
		{
			if (l[j] == 0)
			{
				while (i--)
					b++;
				return (b);
			}
			j++;
		}
	}
	return (0);
}
