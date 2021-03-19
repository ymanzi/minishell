/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llexer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 09:18:13 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/11 09:51:48 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_free(t_lexer *lex)
{
	t_lexer	*tmp;

	while (lex)
	{
		free(lex->str);
		tmp = lex->next;
		free(lex);
		lex = tmp;
	}
}

t_lexer	*lexer_listlast(t_lexer *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lexer_listadd_back(t_lexer **alst, t_lexer *new)
{
	t_lexer	*ptr;
	t_lexer	*debut;

	if (new && alst)
	{
		if (!*alst)
			*alst = new;
		else
		{
			debut = *alst;
			ptr = lexer_listlast(debut);
			ptr->next = new;
			new->next = 0;
		}
	}
}
