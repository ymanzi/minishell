/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:26:00 by ymanzi            #+#    #+#             */
/*   Updated: 2019/10/17 14:12:52 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		*((unsigned char*)(dest + i)) = *((unsigned char*)(src + i));
		if (*(unsigned char*)(src + i) == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (0);
}
