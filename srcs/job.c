/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:04:33 by ymanzi            #+#    #+#             */
/*   Updated: 2020/11/11 11:26:11 by ymanzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_ast	*job(void)
{
	t_tok	*save;
	t_ast	*node;

	save = g_my.curtok;
	if (!g_my.curtok)
		return (NULL);
	if ((node = job1()))
		return (node);
	g_my.curtok = save;
	if ((node = job2()))
		return (node);
	g_my.curtok = save;
	return (NULL);
}

t_ast	*job1(void)
{
	t_ast	*cmd_node;
	t_ast	*job_node;
	t_ast	*res;

	if (!(cmd_node = cmd()))
		return (NULL);
	if (!g_my.curtok || g_my.curtok->type != PIPE)
	{
		ast_delete(cmd_node);
		return (NULL);
	}
	g_my.curtok = g_my.curtok->next;
	if (!(job_node = job()))
	{
		ast_delete(cmd_node);
		return (NULL);
	}
	if (!(res = new_ast()))
	{
		free_double_node(cmd_node, job_node);
		return (NULL);
	}
	res->type = NODE_PIPE;
	ast_branch(res, cmd_node, job_node);
	return (res);
}

t_ast	*job2(void)
{
	return (cmd());
}
