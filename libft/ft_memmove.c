/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:17:12 by ymanzi            #+#    #+#             */
/*   Updated: 2019/10/23 13:55:03 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;
	size_t			i;

	if (!(dst || src))
		return (0);
	if (dst == src)
		return (dst);
	i = 0;
	dst_tmp = (unsigned char*)dst;
	src_tmp = (unsigned char*)src;
	if (dst_tmp < src_tmp)
		while (i < n)
		{
			dst_tmp[i] = src_tmp[i];
			i++;
		}
	else
		while (n-- > 0)
			dst_tmp[n] = src_tmp[n];
	return (dst);
}
