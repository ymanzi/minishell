/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:48:39 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/10 16:49:03 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_ast	*option_list(void)
{
	t_ast	*node;
	t_tok	*save;

	save = g_my.curtok;
	if (!g_my.curtok)
		return (NULL);
	if ((node = option_list1()))
		return (node);
	g_my.curtok = save;
	return (NULL);
}

t_ast	*option_list1(void)
{
	char	*save_data;
	t_ast	*res;
	t_ast	*o_node;

	if (!g_my.curtok || g_my.curtok->type != STRING)
		return (NULL);
	save_data = g_my.curtok->data;
	g_my.curtok = g_my.curtok->next;
	o_node = option_list();
	if (!(res = new_ast()))
	{
		ast_delete(o_node);
		return (NULL);
	}
	ast_setdata(res, save_data);
	ast_settype(res, NODE_ARGUMENT);
	ast_branch(res, NULL, o_node);
	return (res);
}
