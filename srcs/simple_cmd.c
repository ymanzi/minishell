/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:21:52 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/11 11:27:35 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_ast	*simple_cmd(void)
{
	t_tok	*save;

	save = g_my.curtok;
	return (simple_cmd1());
}

t_ast	*simple_cmd1(void)
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
	ast_settype(res, NODE_CMDPATH);
	ast_branch(res, NULL, o_node);
	return (res);
}
