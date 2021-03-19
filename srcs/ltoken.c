/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltoken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:00:33 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/09 19:59:27 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*lexer_init(char *str)
{
	t_lexer	*lex;

	if (!(lex = (t_lexer*)malloc(sizeof(t_lexer))))
		return (NULL);
	if (!(lex->str = ft_strdup(str)))
		return (NULL);
	lex->next = 0;
	return (lex);
}

t_tok	*token_init(char *data, int type)
{
	t_tok	*token;

	if (!(token = (t_tok*)malloc(sizeof(t_tok))))
		return (NULL);
	if (!(token->data = ft_strdup(data)))
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

void	token_listadd_front(t_tok **alst, t_tok *new)
{
	if (new && alst)
	{
		if (!*alst)
			*alst = new;
		else
		{
			new->next = *alst;
			*alst = new;
		}
	}
}

t_tok	*token_listlast(t_tok *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	token_listadd_back(t_tok **alst, t_tok *new)
{
	t_tok	*ptr;
	t_tok	*debut;

	if (new && alst)
	{
		if (!*alst)
			*alst = new;
		else
		{
			debut = *alst;
			ptr = token_listlast(debut);
			ptr->next = new;
			new->next = 0;
		}
	}
}
