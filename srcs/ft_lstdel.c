/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:15:43 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/04 18:37:01 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_list	*spec_get_env(t_list **list, char *elem)
{
	t_list	*cur;
	t_list	*prev;

	prev = 0;
	cur = *list;
	while (cur)
	{
		if (!ft_strncmp((char*)(cur->content), elem, ft_strlen(elem))
				&& ((char*)(cur->content))[ft_strlen(elem)] == '=')
		{
			if (!prev)
				return (cur);
			else
				return (prev);
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

void			ft_lstdel(t_list **lst, char *s)
{
	t_list	*elem;
	t_list	*del;

	if (lst && s && ft_strlen(s))
	{
		elem = spec_get_env(lst, s);
		if (elem)
		{
			if (elem == *lst)
			{
				*lst = elem->next;
				del = elem;
			}
			else
			{
				del = elem->next;
				elem->next = del->next;
			}
			free(del->content);
			free(del);
		}
	}
}

void			token_del_vide(t_tok **save, t_tok **tok, t_tok *prev)
{
	if (!prev)
		*save = (*tok)->next;
	else
		prev->next = (*tok)->next;
	free((*tok)->data);
	free(*tok);
	if (!prev)
		*tok = *save;
	else
		*tok = prev->next;
}
