/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:25:07 by ymanzi            #+#    #+#             */
/*   Updated: 2019/10/20 12:14:53 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_mots(char const *s1, char const c)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (s1 == 0)
		return (1);
	while (s1[j])
	{
		if (s1[j] == c)
			i++;
		j++;
	}
	return (i);
}

static char	*free_tab(char **ptr, int i)
{
	while (i >= 0)
		free(ptr[i--]);
	free(ptr);
	return (NULL);
}

static char	**deg(char const *s, char c, int t[], char **ptr)
{
	while (s[t[1] + t[2]])
	{
		if (s[t[1] + t[2]] == c)
		{
			if (t[2] > 0)
			{
				if (!(ptr[t[0]++] = ft_substr(s, t[1], t[2])))
					return ((char**)free_tab(ptr, t[0] - 1));
			}
			else
				t[1]++;
			t[1] += t[2];
			t[2] = -1;
		}
		else if (!(s[t[1] + t[2] + 1]))
			if (!(ptr[t[0]++] = ft_substr(s, t[1], t[2] + 1)))
				return ((char**)free_tab(ptr, t[0] - 1));
		t[2]++;
	}
	ptr[t[0]] = 0;
	return (ptr);
}

char		**ft_split(char const *s, char c)
{
	char	**ptr;
	int		t[3];

	t[0] = 0;
	t[1] = 0;
	t[2] = 0;
	if (s == 0 || !(ptr = (char**)malloc(sizeof(*ptr) * (n_mots(s, c) + 1))))
		return (NULL);
	return (deg(s, c, t, ptr));
}
