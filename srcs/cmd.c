/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:42:50 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/10 16:46:31 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_ast	*cmd(void)
{
	t_tok	*save;
	t_ast	*node;

	if (!g_my.curtok)
		return (NULL);
	save = g_my.curtok;
	if ((node = cmd1()))
		return (node);
	g_my.curtok = save;
	if ((node = cmd2()))
		return (node);
	g_my.curtok = save;
	if ((node = cmd3()))
		return (node);
	g_my.curtok = save;
	if ((node = cmd4()))
		return (node);
	return (NULL);
}

t_ast	*cmd1(void)
{
	t_ast	*s_cmd;
	t_ast	*cmd_node;
	t_ast	*res;

	if (!(s_cmd = simple_cmd()))
		return (NULL);
	if (!g_my.curtok || g_my.curtok->type != SMALLER)
	{
		ast_delete(s_cmd);
		return (NULL);
	}
	g_my.curtok = g_my.curtok->next;
	if (!(cmd_node = cmd()))
	{
		ast_delete(s_cmd);
		return (NULL);
	}
	if (!(res = new_ast()))
	{
		free_double_node(s_cmd, cmd_node);
		return (NULL);
	}
	res->type = NODE_SMALLER;
	ast_branch(res, s_cmd, cmd_node);
	return (res);
}

t_ast	*cmd2(void)
{
	t_ast	*s_cmd;
	t_ast	*cmd_node;
	t_ast	*res;

	if (!(s_cmd = simple_cmd()))
		return (NULL);
	if (!g_my.curtok || g_my.curtok->type != GREATER)
	{
		ast_delete(s_cmd);
		return (NULL);
	}
	g_my.curtok = g_my.curtok->next;
	if (!(cmd_node = cmd()))
	{
		ast_delete(s_cmd);
		return (NULL);
	}
	if (!(res = new_ast()))
	{
		free_double_node(s_cmd, cmd_node);
		return (NULL);
	}
	res->type = NODE_GREATER;
	ast_branch(res, s_cmd, cmd_node);
	return (res);
}

t_ast	*cmd3(void)
{
	t_ast	*s_cmd;
	t_ast	*cmd_node;
	t_ast	*res;

	if (!(s_cmd = simple_cmd()))
		return (NULL);
	if (!g_my.curtok || g_my.curtok->type != DGREATER)
	{
		ast_delete(s_cmd);
		return (NULL);
	}
	g_my.curtok = g_my.curtok->next;
	if (!(cmd_node = cmd()))
	{
		ast_delete(s_cmd);
		return (NULL);
	}
	if (!(res = new_ast()))
	{
		free_double_node(s_cmd, cmd_node);
		return (NULL);
	}
	res->type = NODE_DGREATER;
	ast_branch(res, s_cmd, cmd_node);
	return (res);
}

t_ast	*cmd4(void)
{
	return (simple_cmd());
}
