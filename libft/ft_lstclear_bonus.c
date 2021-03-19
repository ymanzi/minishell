/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:42:04 by ymanzi            #+#    #+#             */
/*   Updated: 2019/10/23 13:48:26 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *debut;
	t_list *suivant;

	if (lst && *lst && del)
	{
		debut = *lst;
		suivant = 0;
		while (debut)
		{
			suivant = (debut->next);
			ft_lstdelone(debut, del);
			debut = suivant;
		}
		*lst = 0;
	}
}
