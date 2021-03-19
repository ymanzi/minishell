/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:51:36 by ymanzi            #+#    #+#             */
/*   Updated: 2019/10/22 14:41:19 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		len = 0;
	if (s == 0 || !(ptr = (char*)malloc(sizeof(*ptr) * (len + 1))))
		return (0);
	while (len-- > 0 && *(s + start + i))
	{
		ptr[i] = s[start + i];
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
