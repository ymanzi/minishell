/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:59:32 by ymanzi            #+#    #+#             */
/*   Updated: 2019/10/23 13:33:12 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
			|| c == '\r' || c == ' ');
}

int			ft_atoi(const char *nptr)
{
	int					moins;
	unsigned long long	nbr;

	moins = 1;
	nbr = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*(nptr++) == '-')
			moins *= -1;
	}
	while (*nptr >= '0' && *nptr <= '9')
		nbr = (10 * nbr + (*(nptr++) - 48));
	if (nbr > 9223372036854775807)
		return ((moins > 0) ? -1 : 0);
	return ((int)(moins * nbr));
}
