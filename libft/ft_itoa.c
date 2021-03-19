/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 20:16:32 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/11 15:49:04 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			get_taille(int n)
{
	int i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*minimum(void)
{
	char *tpr;

	if (!(tpr = (char*)malloc(sizeof(*tpr) * 12)))
		return (0);
	tpr[0] = '-';
	tpr[1] = '2';
	tpr[2] = '1';
	tpr[3] = '4';
	tpr[4] = '7';
	tpr[5] = '4';
	tpr[6] = '8';
	tpr[7] = '3';
	tpr[8] = '6';
	tpr[9] = '4';
	tpr[10] = '8';
	return (tpr);
}

char		*ft_itoa(int n)
{
	char	*tpr;
	int		taille;
	int		n2;

	if (n == (-2147483648))
		return (minimum());
	n2 = n;
	taille = get_taille(n);
	if (!(tpr = (char*)malloc(sizeof(*tpr) * (taille + 1))))
		return (0);
	if (n < 0)
		n *= -1;
	tpr[taille--] = '\0';
	while (n > 9)
	{
		tpr[taille--] = (n % 10) + 48;
		n /= 10;
	}
	tpr[taille--] = (n + 48);
	if (n2 < 0)
		tpr[taille] = '-';
	return (tpr);
}
