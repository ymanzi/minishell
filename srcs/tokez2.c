/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokez2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:31:32 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/12 14:24:17 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	fct_space(char *str, int *tab, int *i)
{
	p_new_token(str, i, tab);
	while (str[(*i)] && (str[(*i)] == ' ' || str[(*i)] == '\t'))
		(*i)++;
}

void	fct_sep(char *str, int *tab, int *i)
{
	if (!(tab[1]) && (str[*i] == '>' || str[*i] == '<'))
		new_token("");
	else if (tab[1] && !tab[2])
	{
		p_new_token(str, i, tab);
		return ;
	}
	tab[0] = 0;
	if (str[*i + 1] && str[*i] == '>' && str[*i + 1] == '>')
		(*i)++;
	if (str[*i] == ';')
		tab[1] = -1;
	(*i)++;
	p_new_token(str, i, tab);
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
}
