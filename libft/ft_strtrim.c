/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:58:58 by ymanzi            #+#    #+#             */
/*   Updated: 2019/10/11 13:42:18 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nombre_debut(char const *s1, char const *set)
{
	int	j;
	int	p;

	p = 0;
	j = 0;
	while (s1[j] && p == 0)
	{
		if (!(ft_strchr(set, s1[j])))
		{
			p = 1;
			j--;
		}
		j++;
	}
	return (j);
}

static int	nombre_fin(char const *s1, char const *set)
{
	int len;
	int	i;
	int	p;
	int j;

	i = 0;
	p = 0;
	len = ft_strlen(s1);
	j = len - 1;
	while (len - i > 0 && p == 0)
	{
		if (!(ft_strchr(set, s1[len - i - 1])))
		{
			j = len - i - 1;
			p = 1;
		}
		i++;
	}
	return (j);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		debut;
	int		fin;
	int		j;
	int		i;

	j = 0;
	i = 0;
	if (s1 == 0 || set == 0)
		return (0);
	debut = nombre_debut(s1, set);
	fin = nombre_fin(s1, set);
	if (!(ptr = (char*)malloc(sizeof(*ptr) * (fin - debut + 2))))
		return (0);
	while (j < debut)
		j++;
	while (j < (fin + 1) && s1[j])
	{
		ptr[i++] = s1[j];
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}
