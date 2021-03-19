/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:01:27 by ymanzi            #+#    #+#             */
/*   Updated: 2019/10/20 16:32:40 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *ptr;
	t_list *debut;

	if (new && alst)
	{
		if (!*alst)
			*alst = new;
		else
		{
			debut = *alst;
			ptr = ft_lstlast(debut);
			ptr->next = new;
			new->next = 0;
		}
	}
}
