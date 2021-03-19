/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:21:51 by ymanzi            #+#    #+#             */
/*   Updated: 2019/10/20 16:34:20 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *ptr;

	if ((ptr = (t_list*)malloc(sizeof(*ptr))))
	{
		ptr->content = (void*)content;
		ptr->next = 0;
	}
	return (ptr);
}
