/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:00:23 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/11 15:00:33 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		parsing_tok(t_tok *tok)
{
	while (tok)
	{
		parsing_suite(&(tok->data));
		tok = tok->next;
	}
}

int			is_al_num_u(char c)
{
	return ((ft_isalpha(c) || ft_isdigit(c) || c == '_'));
}
